#ifndef PROCEDURE_H
#define PROCEDURE_H

#define DIM_BUFFER 10
#define NUM_STUDENTI 30
#define NUM_ADDETTI 5

// Semafori
#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX_STUDENTI 2
#define MUTEX_ADDETTI 3

typedef struct {
    int buffer[DIM_BUFFER];
    int testa;
    int coda;
    int studenti_vivi;
} coda_stampa;

// Prototipi
void studente(coda_stampa *coda, int semid);
void addetto(coda_stampa *coda, int semid);

#endif