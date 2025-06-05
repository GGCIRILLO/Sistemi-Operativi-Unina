#ifndef _HEADER_
#define _HEADER_

#include "monitor_hoare.h"
#include "semafori.h"
#include <stdlib.h>
#include <stdio.h>

#define DIM 3

/* TBD: Aggiungere le variabili per la sincronizzazione con 
     *      l'algoritmo del vettore di stato
     */
#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define CV_PROD 0
#define CV_CONS 1

#define MUTEX 0

typedef struct {

    int buffer[DIM];

    /* TBD: Aggiungere le variabili per la sincronizzazione con 
     *      l'algoritmo del vettore di stato
     */
    int stato[DIM];
    int num_liberi;
    int num_occupati;

    Monitor m;

} VettoreProdCons;

typedef struct {

    int buffer;

    int sem_id;  // Utilizzare questa variabile per la mutua esclusione

} BufferMutuaEsclusione;

void inizializza_vettore(VettoreProdCons * p);
void produci(VettoreProdCons * p, int valore);
int consuma(VettoreProdCons * p);
void rimuovi_vettore(VettoreProdCons * p);

void inizializza_buffer(BufferMutuaEsclusione * p);
void aggiorna(BufferMutuaEsclusione * p, int valore);
void rimuovi_buffer(BufferMutuaEsclusione * p);

static inline void die(const char* m){
    perror(m);
    exit(1);
}

#endif
