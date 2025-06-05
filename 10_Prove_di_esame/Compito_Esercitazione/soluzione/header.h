#ifndef _HEADER_
#define _HEADER_

// aggiunte per die 
#include <stdio.h>
#include <stdlib.h>

#include "monitor_hoare.h"
#include "semafori.h"

#define DIM 3

// Variabili per la sincronizzazione
#define MUTEX 0

#define VARCOND_P 0
#define VARCOND_C 1
#define NUM_CV 2

// struttura per risolvere il problema prod-cons
typedef struct {

    int buff[DIM];
    int testa;
    int coda;
    
    Monitor m;

} VettoreProdCons;


// struttura per la gestione in mutua esclusione del buffer
typedef struct {

    int val;
    int sem_id;

} BufferMutuaEsclusione;

void inizializza_vettore(VettoreProdCons * p);
void produci(VettoreProdCons * p, int valore);
int consuma(VettoreProdCons * p);
void rimuovi_vettore(VettoreProdCons * p);

void inizializza_buffer(BufferMutuaEsclusione * p);
void aggiorna(BufferMutuaEsclusione * p, int valore);
void rimuovi_buffer(BufferMutuaEsclusione * p);

// util per errori
static inline void die(const char *msg){
    perror(msg);
    exit(1);
}

#endif
