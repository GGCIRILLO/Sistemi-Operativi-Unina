#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "header.h"

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 5

#define PRODUZIONI 10
#define CONSUMAZIONI 4

void produttore(VettoreProdCons * vettore);
void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer);

int main() {

    // inizializzo memorie condivise per vettore e buffer

    // inizializzo strutture

    // creo processi figli

    for(int i=0; i<NUM_PRODUTTORI; i++) {

        
    }


    for(int i=0; i<NUM_CONSUMATORI; i++) {

        
    }


    // attendo terminazione figli

    
    // rimuovo strutture

    return 0;

}

void produttore(VettoreProdCons * vettore) {

    srand(getpid());
    
    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[MAIN PRODUTTORE] Produzione: %d\n", valore);

        // produzione effettiva
    }

}

void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer) {

    srand(getpid());

    for(int i=0; i<CONSUMAZIONI; i++) {

        int valore;

        // consumo e aggiornamento effettivi

        printf("[MAIN CONSUMATORE] Consumazione: %d\n", valore);

    }
}
