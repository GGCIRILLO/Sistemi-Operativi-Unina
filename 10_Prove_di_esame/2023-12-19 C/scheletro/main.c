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


    VettoreProdCons * vettore = /* TBD: Allocare la struttura dati */

    BufferMutuaEsclusione * buffer = /* TBD: Allocare la struttura dati */


    inizializza_vettore(vettore);
    inizializza_buffer(buffer);


    for(int i=0; i<NUM_PRODUTTORI; i++) {

        /* TBD: Creare i processi produttori, e fargli chiamare la
         *      funzione "produttore()"
         */
    }


    for(int i=0; i<NUM_CONSUMATORI; i++) {

        /* TBD: Creare i processi consumatori, e fargli chiamare la
         *      funzione "consumatore()"
         */
    }


    /* TBD: Attendere la terminazione dei processi figli */


    rimuovi_buffer(buffer);
    rimuovi_vettore(vettore);


    /* TBD: De-allocare le strutture dati */

    return 0;

}

void produttore(VettoreProdCons * vettore) {

    srand(getpid());
    
    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[MAIN PRODUTTORE] Produzione: %d\n", valore);

        /* TBD: Chiamare il metodo "produci()" del monitor */
    }

}

void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer) {

    srand(getpid());

    for(int i=0; i<CONSUMAZIONI; i++) {

        int valore;

        /* TBD: Chiamare il metodo "consuma()" del monitor */

        printf("[MAIN CONSUMATORE] Consumazione: %d\n", valore);

        /* TBD: Chiamare il metodo "aggiorna()", passandogli 
         *      il valore che è stato appena consumato
         */
    }
}
