/* setup.c – crea e inizializza le risorse, poi avvia 2 worker */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#include "semafori.h"

#define FTOK_PATH "."
#define PROJ_MEM  'M'
#define PROJ_SEM  'S'

static void die(const char *m){ perror(m); exit(1); }

int main(void)
{
    key_t k_mem = ftok(FTOK_PATH, PROJ_MEM);
    key_t k_sem = ftok(FTOK_PATH, PROJ_SEM);
    if (k_mem == -1 || k_sem == -1) die("ftok");

    /* crea “da zero”; fallisce se esistono già                         */
    int shmid = shmget(k_mem, sizeof(int), IPC_CREAT | IPC_EXCL | 0664);
    if (shmid < 0) die("shmget");

    int semid = semget(k_sem, 1, IPC_CREAT | IPC_EXCL | 0664);
    if (semid < 0) die("semget");

    int *val = shmat(shmid, NULL, 0);
    if (val==(void*)-1) die("shmat");

    *val = 0;                                     /* contatore           */
    if (semctl(semid,0,SETVAL,1)<0) die("semctl");

    printf("[SETUP] create OK   shmid=%d  semid=%d\n", shmid, semid);

    /* lancia due worker passandogli NULL: i worker useranno ftok        */
    for(int i=0;i<2;i++){
        if(fork()==0){
            execl("./worker","worker",(char*)0);
            die("execl worker");
        }
    }

    for(int i=0;i<2;i++) wait(NULL);

    printf("[SETUP] counter finale = %d\n", *val);

    return 0;          /* cleanup affidato a cleanup.c o a un altro run */
}