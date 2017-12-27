//
//	applicant.c
//	hw3
//	150140707
//	Muhammet UÇAN
//
#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <sys/wait.h>
#include "sem_functions.h"

// created child proceses and for each child proecces, which are applicants, 
// neccesery key values created, shared memory for status information created

int main(int argc, char const *argv[])
{
    if (argc == 1) {
        return 0;
    }
	int f; // return value of fork
    int numofApp = *argv[1]-'0'; // number of applicant given by user
	int child[numofApp]; // array that keeps the id of child's in case of need
    int i; // int for for loop
    
    key_t KEYSEM, KEYSEM2, KEYSHM; // keys for sempahore and shared memory
    int status_memid = 0; // shared memory id
    int interview_sem = 0, training_sem = 0; // sync semaphore ids for waiting end of interview and training
    int *statusOfApplicant; // allocate a shared memory location
	
    // creating number of child proceses given by user
	for (i = 1; i <= numofApp; ++i)
	{
		f= fork();
		if (f==-1) {
			printf("Fork error\n");
			exit(1);
		}
        if (f==0) {
            // creating different keys for each child applicant
            // creating semephore for human resources department
            KEYSEM = ftok(get_current_dir_name() ,3*i-2);
            // creating sempahore with key=KEYSEM
            interview_sem = semget(KEYSEM, 1, IPC_CREAT | 0700);
            // setting value 0
            semctl(interview_sem, 0, SETVAL,0);
            
            // creating semaphore for trail department
            KEYSEM2 = ftok(get_current_dir_name() ,3*i-1);
            // creating semaphore with key=KEYSEM2
            training_sem = semget(KEYSEM2, 1, IPC_CREAT | 0700);
            // setting initial value to 0
            semctl(training_sem, 0, SETVAL,0);
            
            // creating shared memory for status
            KEYSHM = ftok(get_current_dir_name() ,3*i);
            // creating a shared memory area with the size of an int
            status_memid = shmget(KEYSHM, sizeof(int), IPC_CREAT | 0700);
            // attaching the shared memory segment identified by status_memid to the adress space of the calling process
            statusOfApplicant = (int *) shmat(status_memid, 0, 0);
            *statusOfApplicant = 0; // initial status

            break;
        }
        else if (f>0) {
            child[i] = f;
        }
	}
	
	if (f!=0) {
        // parent
        wait(NULL);
	} 
	else {
        // child, create status for each child
        // wait for interview semaphore from hr
        sem_wait(interview_sem,1);
        // applicants who are NOT accepted for trail
        if (*statusOfApplicant == 1) {
            // removing the created semaphores and shared memory
            semctl(interview_sem, 0, IPC_RMID,0);
            semctl(training_sem, 0, IPC_RMID,0);
            shmdt(statusOfApplicant);
            shmctl(status_memid, IPC_RMID, NULL);
            exit(1);
        }

        // applicants who are accepted for trail
        if (*statusOfApplicant == 2 ) {
        }
        

        // wait for training semaphore from trail
        sem_wait(training_sem,1);
        // applicants who are NOT accepted for job
        if (*statusOfApplicant == 3) {
            // removing the created semaphores and shared memory
            semctl(interview_sem, 0, IPC_RMID,0);
            semctl(training_sem, 0, IPC_RMID,0);
            shmdt(statusOfApplicant);
            shmctl(status_memid, IPC_RMID, NULL);
            exit(1);
        }
        // applicants who are accpeted for job
        if (*statusOfApplicant == 4);

        // removing the created semaphores and shared memory
        semctl(interview_sem, 0, IPC_RMID,0);
        semctl(training_sem, 0, IPC_RMID,0);
        shmdt(statusOfApplicant);
        shmctl(status_memid, IPC_RMID, NULL);
	}
	return 0;
}
