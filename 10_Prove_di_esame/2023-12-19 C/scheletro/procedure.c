#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons * p) {

    /* TBD: Inizializzare la struttura dati "VettoreProdCons" */

}

void produci(VettoreProdCons * p, int valore) {

    /* TBD: Implementare la sincronizzazione, mediante
     *      l'algoritmo del vettore di stato
     */

}

int consuma(VettoreProdCons * p) {

    int valore;

    /* TBD: Implementare la sincronizzazione, mediante
     *      l'algoritmo del vettore di stato
     */

    return valore;

}

void rimuovi_vettore(VettoreProdCons * p) {

    /* TBD: De-inizializzare la struttura dati "VettoreProdCons" */
}


void inizializza_buffer(BufferMutuaEsclusione * p) {

    /* TBD: Inizializzare la struttura dati "BufferMutuaEsclusione" */
}

void aggiorna(BufferMutuaEsclusione * p, int valore) {

    /* TBD: Aggiungere la sincronizzazione per la mutua esclusione */

    p->buffer += valore;

    printf("[AGGIORNA] Nuovo valore del buffer: %d\n", p->buffer);
}

void rimuovi_buffer(BufferMutuaEsclusione * p) {

    /* TBD: De-inizializzare la struttura dati "BufferMutuaEsclusione" */
}


