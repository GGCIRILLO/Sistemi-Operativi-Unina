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

    int buffer[DIM];
    int testa;
    int coda;
    int elementi;

    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;

} CodaCircolare;

typedef struct {

    int buffer_regali;

    int consegne_effettuate;

    pthread_mutex_t mutex;
    pthread_cond_t cv_babbo;

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
void* Produttore(void* p);
void* Consumatore(void* p);
void* Babbo_Natale(void* p);

#endif
