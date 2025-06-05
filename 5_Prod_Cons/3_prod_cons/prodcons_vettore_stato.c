#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"

static void die (const char *msg){
    perror(msg);
    exit(1);
}

int main() {

    // TODO: Creare chiave per la shared memory
    key_t k_shm = IPC_PRIVATE;

    // TODO: Allocare shared memory della dimensione di struct prodcons
    int ds_shm = shmget(k_shm, sizeof(struct prodcons), IPC_CREAT |0664);
    if(ds_shm<0) die("Errore shmget"); 

    // TODO: Attaccare la shared memory al processo
    struct prodcons * p = (struct prodcons*) shmat(ds_shm, NULL, 0);
    if (p==(void*)-1) die("Errore shmat");

    // TODO: Inizializzare vettore stato[] a BUFFER_VUOTO
    for(int i=0;i<DIM_BUFFER;i++) p->stato[i]=BUFFER_VUOTO;
    

    // TODO: Creare chiave per i semafori
    key_t k_sem = IPC_PRIVATE;

    // TODO: Allocare 4 semafori (SPAZIO_DISPONIBILE, MESSAGGIO_DISPONIBILE, MUTEX_C, MUTEX_P)
    int ds_sem = semget(k_sem, 4, IPC_CREAT|0664);
    if (ds_sem<0) die("Errore semget");

    // TODO: Inizializzare:
    // - SPAZIO_DISPONIBILE a DIM_BUFFER
    // - MESSAGGIO_DISPONIBILE a 0
    // - MUTEX_C e MUTEX_P a 1
    semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
    semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    semctl(ds_sem, MUTEX_P, SETVAL, 1);
    semctl(ds_sem, MUTEX_C, SETVAL, 1);

    // TODO: Creare i processi figli consumatori con fork()
    // - In ogni figlio:
    //   - stampare messaggio di avvio
    //   - inizializzare srand con getpid()*time(NULL)
    //   - chiamare consumatore()
    //   - exit(1)
    for(int i=0;i<NUM_CONSUMATORI;i++){
        pid_t pid = fork();
        if(pid<0) die("Errore fork");
        if(pid==0){
            printf("Avvio Figlio consumatore PID=%d\n", getpid());
            srand(getpid()*time(NULL));
            consumatore(p, ds_sem);
            exit(1);
        }
    }

    // TODO: Creare i processi figli produttori con fork()
    // - In ogni figlio:
    //   - stampare messaggio di avvio
    //   - inizializzare srand con getpid()*time(NULL)
    //   - chiamare produttore()
    //   - exit(1)
    for (int i=0;i<NUM_PRODUTTORI;i++){
        pid_t pid = fork();
        if(pid<0) die("Errore fork");
        if(pid==0){
            printf("Avvio Figlio produttore PID=%d\n", getpid());
            srand(getpid()*time(NULL));
            produttore(p, ds_sem);
            exit(1);
        }
    }

    // TODO: Attendere la terminazione dei figli produttori con wait()
    for(int i=0;i<NUM_PRODUTTORI;i++) {
        pid_t term_pid = wait(NULL);
        printf("Figlio produttore PID=%d terminato\n", term_pid);
    }

    // TODO: Attendere la terminazione dei figli consumatori con wait()
    for(int i=0;i<NUM_CONSUMATORI;i++) {
        pid_t term_pid = wait(NULL);
        printf("Figlio consumatore PID=%d terminato\n", term_pid);
    }
    

    // TODO: Deallocare la shared memory
    shmctl(ds_shm, IPC_RMID, NULL);
    // TODO: Deallocare il set di semafori
    semctl(ds_sem, 0, IPC_RMID);

    return 0;
}