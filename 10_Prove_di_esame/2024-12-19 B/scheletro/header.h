#ifndef HEADER_H
#define HEADER_H

#include <pthread.h>

#define DIM 6
#define GIOCATTOLI_PER_PROD 15
#define REGALI_PER_CONSEGNA 5
#define PRELIEVI_PER_CONS 10
#define CONSEGNE 6

#define NPROD 6
#define NCONS 3
/*
    TODO: completare strutture per la gestione della coda circolare e del buffer condivisi
*/

typedef struct {

} CodaCircolare;

typedef struct {

} BufferBabbo;

void inizializza_coda(CodaCircolare *coda);
void distruggi_coda(CodaCircolare *coda);
void produci(CodaCircolare *coda, int giocattolo);
void consuma(CodaCircolare *coda);

void inizializza_buffer(BufferBabbo *buffer);
void distruggi_buffer(BufferBabbo *buffer);
void aggiorna_conteggio(BufferBabbo *buffer);
void consegna(BufferBabbo *buffer);

/*
    TODO: completare firma starting routine dei thread
*/

#endif
