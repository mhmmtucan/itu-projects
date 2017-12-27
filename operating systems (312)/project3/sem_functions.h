//
//  sem_functions.h
//  hw3
//	150140707
//	Muhammet UÇAN
//
#ifndef sem_functions_h
#define sem_functions_h

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

#endif /* sem_functions_h */
