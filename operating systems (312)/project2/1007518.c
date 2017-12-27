//
//  Muhammet UÇAN
//  150140707
//  Homework-2
// 

// input.txt file is not included in zip file!

#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int s;
void create(char *argv[]) {
    int someKey = ftok(strcat(get_current_dir_name(), argv[0]), 1);
    s = semget(someKey, 1, 0700|IPC_CREAT);
    semctl(s, 0, SETVAL, 1);
}

void sem_signal(int semid, int val) {
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = val;
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

void sem_wait(int semid, int val) {
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = (-1*val);
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

void increase(int sid) {
    sem_signal(s, 1);
}

void decrease(int sid) {
    sem_wait(s, 1);
}

typedef struct {
    int applicantID;
    int interviewTime;
    int interviewed;
    int registered;
} Applicant;

Applicant* applicants;

int numberOfApplicant;
int indexOfApplicant;

int numOfApplicantsForRegistration;
int numOfApplicantsForInterview;
int registrationDone;
int registrationTime;


// function for applying applicants, taking file and creating applicants 
void apply(char* file_name) {
    FILE* myFile = fopen((char*)file_name, "r");
    int interviewTime;
    int i = 0;
    
    while(fscanf(myFile, "%d", &interviewTime) == 1) {
        Applicant temp = {i+1,interviewTime,0,0};
        applicants[i] = temp;
        
        numOfApplicantsForRegistration++;
        numberOfApplicant++;
        printf("Applicant %d applied to the receptionist\n", ++i);
    }
}

// applicants registered for interview
void* registration(void* arg) {
    int i = 0;
    while(i < numberOfApplicant) {
        if(numOfApplicantsForRegistration > 0) {
            sleep(registrationTime);
            decrease(s);
            applicants[i].registered = 1;
            numOfApplicantsForRegistration--;
            numOfApplicantsForInterview++;
            printf("Applicant %d's registration is done\n", ++i);
            increase(s);
        }
    }
    registrationDone = 1;
    pthread_exit(NULL);
}

void* interview(void* t) {
    long tid = (long) t;
    
    while(indexOfApplicant < numberOfApplicant) {
        int temp_indexOfApplicant = 0;
        int found = 0;
        if(numOfApplicantsForInterview > 0) {
            decrease(s);
            if(applicants[indexOfApplicant].registered == 1 && applicants[indexOfApplicant].interviewed == 0) {
                found = 1;
                temp_indexOfApplicant = indexOfApplicant;
                applicants[indexOfApplicant].interviewed = 1;
                numOfApplicantsForInterview--;
                indexOfApplicant++;
            }
            increase(s);
            if(found) {
                printf("Interviewer %ld started interview with Applicant %d\n", tid, temp_indexOfApplicant+1);
                sleep(applicants[temp_indexOfApplicant].interviewTime/10);
                printf("Interviewer %ld finished interview with Applicant %d\n", tid, temp_indexOfApplicant+1);
            }
        }
        if(numOfApplicantsForInterview == 0 && registrationDone) {
            break;
        }
    }
    pthread_exit(NULL);
}

void delete_applicants() {
    int i = 0;
    free(applicants);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("%s\n", "Arguments are not valid"); 
		exit(-1);
	}

    // in order to find how many applicants are going to be created, to make a dynamic array of applicants
    size_t size = 0;
    int dummyNum;
    FILE* myFile = fopen(argv[1], "r");
    while (fscanf(myFile,"%d",&dummyNum) ==  1) size++;
    fclose(myFile);

    applicants = (Applicant*) malloc(sizeof(Applicant) * size);
    
    numOfApplicantsForRegistration = 0;
    numOfApplicantsForInterview = 0;
    numberOfApplicant = 0;
    indexOfApplicant = 0;
    registrationDone = 0;
    registrationTime = *(argv[2]) - '0';
    
    apply(argv[1]);

    setvbuf(stdout, (char*) NULL, _IONBF, 0);
    create(argv);
    
    pthread_t thread[4];
    pthread_create(&thread[0], NULL, registration, NULL);
    long t=1;
    pthread_create(&thread[t], NULL, interview, (void*) t++);
    pthread_create(&thread[t], NULL, interview, (void*) t++);
    pthread_create(&thread[t], NULL, interview, (void*) t++);
    
    semctl(s, 0, IPC_RMID, 0);
    
    pthread_exit(NULL);
    delete_applicants();
    printf("All applicants have interviewed successfully.");
}