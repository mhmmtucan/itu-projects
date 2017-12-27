//
//	trail.c
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

// set neccesery status value for each trained applicant

int *interviewDone; // shared variable in order to check whether interview finished or not 
applicant *sharedApplicant; // shared memory between hr and trail
int mutex_hr_trail; // semaphore between hr and trail

void* training(void* t) {
    long tid = (long) t;
    while (!*interviewDone || sharedApplicant->isTrained == 0) {
        // mutex part
        sem_wait(mutex_hr_trail,1);
        // take shared applicant
        applicant temp = *sharedApplicant;
        int flag = 0;
        // train applicant
        if (sharedApplicant->isTrained == 0) {
            temp.isTrained = 1;
            flag = 1;
            *sharedApplicant = temp;
        }
        sem_signal(mutex_hr_trail,1);
        
        if (flag) {
            int *shared_status = (int *) shmat(temp.memoryID,0,0); // attachment
            printf("Trainer %ld started training with applicant %d (status of applicant %d :%d)\n",tid,temp.applicantID,temp.applicantID,*shared_status);
            sleep(temp.trainingTime);
            
            if (temp.validForJob == 1) *shared_status = 4;
            else *shared_status = 3;
            
            printf("Trainer %ld finished training with applicant %d (status of applicant %d :%d)\n",tid,temp.applicantID,temp.applicantID,*shared_status);
            
            shmdt(shared_status); // deattachment
            sem_signal(temp.trainingID,1); // signal waiting applicant in applicant.c
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		return 0;
	}
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
    *interviewDone = 0; // initial value

    pthread_t threads[4];
    // threads for trainers
    pthread_create(&threads[0],NULL,training, (void*)1);
    pthread_create(&threads[1],NULL,training, (void*)2);
    pthread_create(&threads[2],NULL,training, (void*)3);
    pthread_create(&threads[3],NULL,training, (void*)4);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    
    // deleting semaphores and shared memory
    semctl(mutex_hr_trail,0,IPC_RMID,0);
    shmdt(sharedApplicant);
    shmctl(sharedApplicant_memid,IPC_RMID,NULL);
    shmdt(interviewDone);
    shmctl(interviewDone_memid,IPC_RMID,NULL);
    printf("Training process is done.\n");
    pthread_exit(NULL);
    
}
