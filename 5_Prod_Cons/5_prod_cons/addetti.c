#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h> 

#include "procedure.h"

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {

    // TODO: Collegarsi alla memoria condivisa
    key_t k_shm = ftok(".", 'A');
    key_t k_sem = ftok(".", 'B');

    int ds_shm = shmget(k_shm, sizeof(coda_stampa), 0664);
    if (ds_shm<0) die("Errore shmget");

    coda_stampa * coda = (coda_stampa *) shmat(ds_shm, NULL, 0);
    if(coda==(void*)-1) die("Errore shmat");

    // TODO: Collegarsi ai semafori
    int ds_sem = semget(k_sem, 4, 0664);
    if(ds_sem<0) die("Errore semget");

    // TODO: Creare NUM_ADDETTI processi figli
    // Ogni figlio chiama addetto()
    for (int i=0;i<NUM_ADDETTI;i++){
        pid_t pid = fork();
        if(pid<0) die("Errore fork");
        if(pid==0){
            addetto(coda, ds_sem);
            exit(1);
        }
    }
    

    // TODO: Attendere terminazione di tutti i figli
    for (int i=0;i<NUM_ADDETTI;i++) wait(NULL);

    // TODO: Stampa stato finale della shm
    printf("\n--- Stato finale della coda di stampa ---\n");
    printf("Testa: %d\n", coda->testa);
    printf("Coda: %d\n", coda->coda);
    printf("Studenti vivi: %d\n", coda->studenti_vivi);

    for (int i = 0; i < DIM_BUFFER; i++) {
        printf("Buffer[%d]: %d\n", i, coda->buffer[i]);
    }

    // TODO: Deallocare memoria condivisa e semafori
    shmctl(ds_shm, IPC_RMID, NULL);
    semctl(ds_sem, 0, IPC_RMID);

    return 0;
}