/* cleanup.c – rimuove shared-memory e semaforo */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define FTOK_PATH "."
#define PROJ_MEM  'M'
#define PROJ_SEM  'S'

static void die(const char *m){ perror(m); exit(1); }

int main(void)
{
    key_t k_mem = ftok(FTOK_PATH, PROJ_MEM);
    key_t k_sem = ftok(FTOK_PATH, PROJ_SEM);
    if (k_mem == -1 || k_sem == -1) die("ftok");

    int shmid = shmget(k_mem, sizeof(int), 0);
    int semid = semget(k_sem, 1,          0);
    if (shmid<0 || semid<0) die("risorse non trovate");

    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid,0, IPC_RMID);

    puts("[CLEAN] risorse rimosse");
    return 0;
}