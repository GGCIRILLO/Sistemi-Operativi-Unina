/* worker.c – apre le risorse esistenti, incrementa 100 volte */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
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

    int shmid = shmget(k_mem, sizeof(int), 0);   /* ottiene esistente */
    if (shmid < 0) die("shmget open");

    int semid = semget(k_sem, 1, 0);
    if (semid < 0) die("semget open");

    int *val = shmat(shmid, NULL, 0);
    if (val==(void*)-1) die("shmat");

    for(int j=0;j<100;j++){
        Wait_Sem(semid,0);
        (*val)++;
        Signal_Sem(semid,0);
    }

    _exit(0);
}