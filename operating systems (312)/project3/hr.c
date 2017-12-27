//
//	hr.c
//	hw3
//	150140707
//	Muhammet UÇAN
//
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string.h>
#include <sys/shm.h>
#include "queue.h"
#include "sem_functions.h"
#define KEYSEM3 ftok(get_current_dir_name() ,150)

// all applicants read from file and registered for interview
// if avaliable sent to trail department for training through shared memory with type of struct

int sem_id; // semaphore id between register and interview

// shared between hr and trail
int mutex_hr_trail; // binary semaphore for mutual exclusion between hr and trail
applicant *sharedApplicant; // sending applicant information to trail departmant
int *interviewDone; // shared memory for trail signal

// queue for inserting all applicants read from file
Queue *applicantQueue;
// applicant queue who is avaliable for interview, i.e. registered
Queue *interviewQueue;
// flag for registration proccess in order to check whether or nof finished
int registrationDone;
int registrationTime;

void read_from_file(char* file_name) {
    // assigning inital values
    int interviewTime = 0;
    int trainingTime=0;
    int validForTrail=0;
    int validForJob=0;
    int i = 0;
    FILE *fp = fopen(file_name,"r");
    // take first line for registrationTime
    fscanf(fp, "%d",&registrationTime);
    printf("Registration time is: %d\n",registrationTime);
    while(fscanf(fp, "%d %d %d %d", &interviewTime, &trainingTime, &validForTrail, &validForJob) == 4) { 
        // create and assign values from file to the applicant

        applicant temp;
        temp.interviewTime = interviewTime;
        temp.trainingTime = trainingTime;
        temp.validForTrail = validForTrail;
        temp.validForJob = validForJob;
        temp.isRegistered = 0;
        temp.isInterviewed = 0;
        temp.isTrained = 0;
        temp.applicantID = ++i;
        int KEYSEM = ftok(get_current_dir_name() ,3*i-2);
        // creating sempahore with key=KEYSEM
        int interview_sem = semget(KEYSEM, 1, IPC_CREAT | 0700);
        // setting value 0
        semctl(interview_sem, 0, SETVAL,0);
        
        // creating semaphore for trail department
        int KEYSEM2 = ftok(get_current_dir_name() ,3*i-1);
        // creating semaphore with key=KEYSEM2
        int training_sem = semget(KEYSEM2, 1, IPC_CREAT | 0700);
        // setting initial value to 0
        semctl(training_sem, 0, SETVAL,0);
        
        // creating shared memory for status
        int KEYSHM = ftok(get_current_dir_name() ,3*i);
        // creating a shared memory area with the size of an int
        int status_memid = shmget(KEYSHM, sizeof(int), IPC_CREAT | 0700);
        // attaching the shared memory segment identified by status_memid to the adress space of the calling process
        int *statusOfApplicant = (int *) shmat(status_memid, 0, 0);
        // initial value for status
        *statusOfApplicant = 0;
        
        // keeping value of interview, training semaphore and status memory id in applicant struct in order to signal later
        temp.interviewID = interview_sem;
        temp.trainingID = training_sem;
        temp.memoryID = status_memid;
        shmdt(statusOfApplicant);
        printf("Applicant %d applied to the receptionist (status of applicant %d: 0)\n",i,i);
        // add newly created applicant to general queue
        enqueue(applicantQueue, createNode(&temp));
    }
}

void* register_applicants(void* arg) {
    int i=0;
    while (!isEmpty(applicantQueue)) {
        sleep(registrationTime);
        Node * temp = dequeue(applicantQueue);
        sem_wait(sem_id,1);
        temp->data.isRegistered=1;
        if (temp) enqueue(interviewQueue,createNode(&(temp->data)));
        i++;
        printf("Applicant %d's registration is done (status of applicant %d: 0)\n", i,i);
        sem_signal(sem_id, 1);
    }
    registrationDone = 1;
    printf("Registration process is done.\n");
    pthread_exit(NULL);
}

void* interview(void* t) {
    
    long tid = (long)t;
    while (!registrationDone || !isEmpty(interviewQueue)) {
        Node *temp = NULL;
        sem_wait(sem_id, 1);
        
        if (!isEmpty(interviewQueue)) temp = dequeue(interviewQueue);
        sem_signal(sem_id, 1);
        
        if(temp) {
            // attachment of memory to proccess
            int *shared_status = (int*) shmat(temp->data.memoryID, 0,0);
            if (temp != NULL) temp->data.isInterviewed = 1;
            printf("Interviewer %d started interview with applicant %d (status of applicant %d: %d)\n", tid, temp->data.applicantID, temp->data.applicantID, *shared_status);
            sleep(temp->data.interviewTime);

            // if accepted for trail or not, change status accordoingly
            if (temp->data.validForTrail == 1) *shared_status = 2;
            else *shared_status = 1;

            printf("Interviewer %d finished interview with applicant %d (status of applicant %d: %d)\n", tid, temp->data.applicantID, temp->data.applicantID, *shared_status);
            // signal interview semaphore id waiting for applicant in applicant.c 
            sem_signal(temp->data.interviewID, 1);
            
            // mutual excluison part for hr and trail
            sem_wait(mutex_hr_trail,1);
            // if applicant valid for training share data and use in trail.c
            if (*shared_status==2) {
                *sharedApplicant = temp->data;
            }
            // deattach memory
            shmdt(shared_status);
            sem_signal(mutex_hr_trail,1);
            
        }
        if (isEmpty(interviewQueue) && registrationDone == 1) {
            break;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("%s\n", "Give input file!");
		return 0;
	}
    applicantQueue = createQueue();
    interviewQueue = createQueue();
    registrationDone = 0;
    
    read_from_file(argv[1]);
    setvbuf(stdout, (char*) NULL, _IONBF, 0);
    // setting semaphore key for semaphore between register and interview
    sem_id = semget(KEYSEM3,1,0700|IPC_CREAT);
    // setting initial value to 1 in order to have mutual exclusion
    semctl(sem_id , 0, SETVAL, 1);
    
    // setting necessary values for sempahores and shared memory between trail and hr
    int mutex_hr_trail_key = ftok(get_current_dir_name(),160);
    mutex_hr_trail = semget(mutex_hr_trail_key,1,0700|IPC_CREAT);
    semctl(mutex_hr_trail,0,SETVAL,1); // because it is mutex
    
    int sharedApplicant_key = ftok(get_current_dir_name(),161);
    int sharedApplicant_memid = shmget(sharedApplicant_key,sizeof(applicant),0700|IPC_CREAT);
    sharedApplicant = (applicant *) shmat(sharedApplicant_memid,0,0);
    sharedApplicant->isTrained = 1; // default value
    
    int interviewDone_key = ftok(get_current_dir_name(),162);
    int interviewDone_memid = shmget(interviewDone_key,sizeof(int),0700|IPC_CREAT);
    interviewDone = (int*) shmat(interviewDone_memid,0,0);
    
    pthread_t threads[4];
    // threads for register and interview
    pthread_create(&threads[0],NULL,register_applicants,NULL);
    pthread_create(&threads[1],NULL,interview, (void*)1);
    pthread_create(&threads[2],NULL,interview, (void*)2);
    pthread_create(&threads[3],NULL,interview, (void*)3);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
	*interviewDone = 1;    
	printf("Interview process is done.\n");
    // deleting semaphores and shared memory
    semctl(sem_id,0,IPC_RMID,0);
    semctl(mutex_hr_trail,0,IPC_RMID,0);
    shmdt(sharedApplicant);
    shmctl(sharedApplicant_memid,IPC_RMID,NULL);
    shmdt(interviewDone);
    shmctl(interviewDone_memid,IPC_RMID,NULL);
    
    deleteQueue(applicantQueue);
    deleteQueue(interviewQueue);
    pthread_exit(NULL);
}
