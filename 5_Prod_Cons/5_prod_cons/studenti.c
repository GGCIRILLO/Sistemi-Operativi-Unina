#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>      
#include <sys/wait.h> 

#include "procedure.h"

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {

    // TODO: Creare chiavi IPC
    key_t k_shm = ftok(".", 'A');
    key_t k_sem = ftok(".", 'B');

    // TODO: Creare e inizializzare memoria condivisa (testa e coda a 0, studenti a NUM_STUDENTI)
    int ds_shm = shmget(k_shm, sizeof(coda_stampa), IPC_CREAT|0664);
    if(ds_shm<0) die("Errore shmget");

    coda_stampa * p = (coda_stampa *) shmat(ds_shm, NULL, 0);
    if(p==(void*)-1) die("Errore shmat");

    p->testa = 0;
    p->coda = 0;
    p->studenti_vivi = NUM_STUDENTI;

    // TODO: Creare e inizializzare semafori (SPAZIO a 10, MESS a 0, MUTEX a 1)
    int ds_sem = semget(k_sem, 4, IPC_CREAT |0664);
    if (ds_sem<0) die("Errore semget");

    semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
    semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    semctl(ds_sem, MUTEX_STUDENTI, SETVAL, 1);
    semctl(ds_sem, MUTEX_ADDETTI, SETVAL, 1);

    // TODO: Creare NUM_STUDENTI processi figli
    // Ogni figlio chiama studente()
    for (int i=0;i<NUM_STUDENTI;i++){
        pid_t pid = fork();
        if(pid<0) die("Errore fork");
        if(pid==0){
            srand(time(NULL)*getpid());
            studente(p, ds_sem);
            exit(1);
        }
    }

    // TODO: Attendere terminazione di tutti i figli
    for (int i=0;i<NUM_STUDENTI;i++) wait(NULL);

    return 0;
}