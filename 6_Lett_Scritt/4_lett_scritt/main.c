#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include "header.h"
#include "semafori.h"

static void die(const char* msg){
    perror(msg);
    exit(1);
}

int main() {
    // TODO: Creare memoria condivisa e semafori
    key_t k_shm = IPC_PRIVATE;
    key_t k_sem = IPC_PRIVATE;

    int ds_shm = shmget(k_shm, sizeof(Monitor), IPC_CREAT|0664);
    if (ds_shm<0) die("Errore shmget");

    Monitor * m = (Monitor *) shmat(ds_shm, NULL, 0);
    if(m==(void*)-1) die("Errore shmat");

    int ds_sem = semget(k_sem, 4, IPC_CREAT|0664);
    if(ds_sem<0) die("Errore semget");

    // TODO: Inizializzare buffer e semafori
    m->status_code=0;
    strcpy(m->diagnostic_message, "OK");
    m->numlettori=0;
    m->numscrittori=0;

    semctl(ds_sem, SYNCH, SETVAL, 1);
    semctl(ds_sem, MUTEXL, SETVAL, 1);
    semctl(ds_sem, MUTEXS, SETVAL, 1);
    semctl(ds_sem, MUTEX, SETVAL, 1);

    // TODO: Creare processi figli per lettori e scrittori
    int tot = NUM_S+NUM_L;
    for (int i=0;i<tot;i++){
        pid_t pid = fork();
        if (pid<0) die("Errore fork");
        if(pid==0){
            if(i%2==0){
                int n = (i==0) ? 1 : 2 ;
                Scrittore(ds_sem, m, n);
            } else {
                int n = (i==1) ? 1 : 2 ;
                Lettore(ds_sem, m, n);
            }
            exit(0);
        }
    }
    // TODO: Attendere la terminazione dei figli
    for (int i=0;i<tot;i++){
        int s;
        pid_t pid = wait(&s);
        if (pid==-1) die("Errore wait");
        else{
            printf("Figlio PID=%d terminato con status=%d\n", pid, s);
        }
    }

    // TODO: Deallocare risorse condivise
    shmctl(ds_shm, IPC_RMID, 0);
    semctl(ds_sem, 0, IPC_RMID);

    return 0;
}