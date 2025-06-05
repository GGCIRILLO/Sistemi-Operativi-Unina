#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "semafori.h"
#include "procedure.h"

static void die(const char *msg){
    perror(msg);
    exit(1);
}

int main() {

    // TODO: Definire la chiave per la memoria condivisa (IPC_PRIVATE o ftok)
    key_t k = IPC_PRIVATE;
    
    // TODO: Allocare la memoria condivisa della dimensione di una struct prodcons
    int shm = shmget(k, sizeof(struct prodcons), IPC_CREAT|0664);
    if (shm<0) die("Errore shmget");

    // TODO: Attaccare la memoria condivisa al processo
    struct prodcons * p = (struct prodcons *) shmat(shm, NULL, 0);
    if (p==(void*)-1) die("Errore shmat");
    
    // TODO: Inizializzare i campi testa e coda della struct (entrambi a 0)
    p->testa = 0;
    p->coda = 0;
    
    // TODO: Definire la chiave per il set di semafori
    key_t k_sem = IPC_PRIVATE;
    
    // TODO: Allocare 4 semafori
    int sem_id = semget(k_sem, 4, IPC_CREAT | 0664);
    if (sem_id<0) die("Errore semget");
    
    // TODO: Inizializzare i semafori:
    // - SPAZIO_DISPONIBILE a DIM_BUFFER
    // - MESSAGGIO_DISPONIBILE a 0
    // - MUTEX_P e MUTEX_C a 1
    semctl(sem_id, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
    semctl(sem_id, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    semctl(sem_id, MUTEX_P, SETVAL, 1);
    semctl(sem_id, MUTEX_C, SETVAL, 1);

    // TODO: Creare NUM_CONSUMATORI processi figli con fork
    // All'interno del figlio:
    // - Stampare messaggio di avvio
    // - Inizializzare srand con getpid() * time(NULL)
    // - Chiamare la funzione consumatore
    // - Terminare il processo con exit
    for (int i=0;i<NUM_CONSUMATORI;i++){

        pid_t pid = fork();
        if (pid<0) die("Errore fork");
        else if (pid==0){
            printf("Avvio [Figlio PID=%d] consumatore\n", getpid());
            srand(getpid()*time(NULL));
            consumatore(p, sem_id);
            exit(0);
        }
    }

    // TODO: Creare NUM_PRODUTTORI processi figli con fork
    // All'interno del figlio:
    // - Stampare messaggio di avvio
    // - Inizializzare srand con getpid() * time(NULL)
    // - Chiamare la funzione produttore
    // - Terminare il processo con exit
    for (int i=0;i<NUM_PRODUTTORI;i++){
        pid_t pid = fork();
        if (pid<0) die("Errore fork");
        else if (pid==0){
            printf("Avvio [Figlio PID=%d] produttore\n", getpid());
            srand(getpid()*time(NULL));
            produttore(p, sem_id);
            exit(0);
        }
    }

    // TODO: Attendere la terminazione di tutti i figli produttori con wait
    for(int i=0;i<NUM_PRODUTTORI;i++){
        pid_t term_pid = wait(NULL);
        printf("[Padre] Figlio produttore PID=%d terminato\n", term_pid);
    }

    // TODO: Attendere la terminazione di tutti i figli consumatori con wait
    for(int i=0;i<NUM_CONSUMATORI;i++){
        pid_t term_pid = wait(NULL);
        printf("[Padre] Figlio consumatore PID=%d terminato\n", term_pid);
    }
    // TODO: Deallocare la memoria condivisa
    shmctl(shm, IPC_RMID, NULL);

    // TODO: Deallocare il set di semafori
    semctl(sem_id, 0, IPC_RMID);

    return 0;
}