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

    int shm_v = shmget(IPC_PRIVATE, sizeof(VettoreProdCons), IPC_CREAT|0664);
    if (shm_v<0) die("shmget");

    VettoreProdCons * vettore = (VettoreProdCons*) shmat(shm_v, NULL, 0); /* TBD: Allocare la struttura dati */
    if (vettore==(void*)-1) die("shmat");

    int shm_b = shmget(IPC_PRIVATE, sizeof(BufferMutuaEsclusione), IPC_CREAT|0664);
    if (shm_b<0) die("shmget");

    BufferMutuaEsclusione * buffer = (BufferMutuaEsclusione*) shmat(shm_b, NULL, 0); /* TBD: Allocare la struttura dati */
    if (buffer==(void*)-1) die("shmat");

    inizializza_vettore(vettore);
    inizializza_buffer(buffer);


    for(int i=0; i<NUM_PRODUTTORI; i++) {

        /* TBD: Creare i processi produttori, e fargli chiamare la
         *      funzione "produttore()"
         */
        pid_t pid = fork();
        if (pid<0) die("fork");
        else if (pid==0){
            printf("[%d] Avvio produttore\n", getpid());
            produttore(vettore);
            exit(0);
        }
    }


    for(int i=0; i<NUM_CONSUMATORI; i++) {

        /* TBD: Creare i processi consumatori, e fargli chiamare la
         *      funzione "consumatore()"
         */
        pid_t pid = fork();
        if (pid<0) die("fork");
        else if (pid==0){
            printf("[%d] Avvio consumatore\n", getpid());
            consumatore(vettore, buffer);
            exit(0);
        }
    }


    /* TBD: Attendere la terminazione dei processi figli */
    while(wait(NULL)>0);


    rimuovi_buffer(buffer);
    rimuovi_vettore(vettore);


    /* TBD: De-allocare le strutture dati */
    shmctl(shm_v, IPC_RMID, NULL);
    shmctl(shm_b, IPC_RMID, NULL);

    return 0;

}

void produttore(VettoreProdCons * vettore) {

    srand(getpid());
    
    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[MAIN PRODUTTORE] Produzione: %d\n", valore);

        /* TBD: Chiamare il metodo "produci()" del monitor */
        produci(vettore, valore);
    }

}

void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer) {

    srand(getpid());

    for(int i=0; i<CONSUMAZIONI; i++) {

        int valore;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
        valore = consuma(vettore);

        printf("[MAIN CONSUMATORE] Consumazione: %d\n", valore);

        /* TBD: Chiamare il metodo "aggiorna()", passandogli 
         *      il valore che è stato appena consumato
         */
        aggiorna(buffer, valore);
    }
}
