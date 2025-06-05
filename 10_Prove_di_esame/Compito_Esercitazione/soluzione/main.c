#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "header.h"

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 5

#define PRODUZIONI 10
#define CONSUMAZIONI 4

void produttore(VettoreProdCons * vettore);
void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer);

int main() {

    // inizializzo memorie condivise per vettore e buffer
    int shm_vcp = shmget(IPC_PRIVATE, sizeof(VettoreProdCons), IPC_CREAT|0664);
    if (shm_vcp<0) die("shmget vcp");
    
    int shm_buff = shmget(IPC_PRIVATE, sizeof(BufferMutuaEsclusione), IPC_CREAT|0664);
    if(shm_buff<0) die("shmget buff");

    VettoreProdCons * p = (VettoreProdCons *) shmat(shm_vcp, NULL, 0);
    if(p==(void*)-1) die("shmat vcp");

    BufferMutuaEsclusione * b = (BufferMutuaEsclusione *) shmat(shm_buff, NULL, 0);
    if (b==(void*)-1) die("shmat buff");

    // inizializzo strutture
    inizializza_vettore(p);

    inizializza_buffer(b);

    // creo processi figli

    for(int i=0; i<NUM_PRODUTTORI; i++) {

        pid_t pid = fork();
        if (pid<0) die("fork prod");
        else if(pid==0){
            printf("Avvio processo figlio produttore pid=%d\n", getpid());
            produttore(p);
            exit(0);
        }
    }


    for(int i=0; i<NUM_CONSUMATORI; i++) {
        pid_t pid = fork();
        if (pid<0) die("fork consum");
        else if(pid==0){
            printf("Avvio processo figlio consumatore pid=%d\n", getpid());
            consumatore(p, b);
            exit(0);
        }
    }


    // attendo terminazione figli
    /*
        for (int i = 0; i < NUM_PRODUTTORI + NUM_CONSUMATORI; i++)
    {
        wait(NULL);
    }
    */
    while(wait(NULL)>0);

    
    // rimuovo strutture
    rimuovi_buffer(b);
    rimuovi_vettore(p);

    shmctl(shm_vcp, IPC_RMID, NULL);
    shmctl(shm_buff, IPC_RMID, NULL);

    return 0;

}

void produttore(VettoreProdCons * p) {

    srand(getpid());
    
    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[MAIN PRODUTTORE %d] Produzione %d: %d\n", getpid(), i, valore);

        // produzione effettiva
        produci(p, valore);
    }

}

void consumatore(VettoreProdCons * p, BufferMutuaEsclusione * b) {

    srand(getpid());

    for(int i=0; i<CONSUMAZIONI; i++) {

        int valore;

        // consumo e aggiornamento effettivi
        valore = consuma(p);

        printf("[MAIN CONSUMATORE %d] Consumazione %d: %d\n", getpid(), i, valore);

        aggiorna(b, valore);

    }
}
