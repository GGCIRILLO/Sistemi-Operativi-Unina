#ifndef __HEADER
#define __HEADER

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM_BUFFER 5

#define NUM_REQ 10

// TODO definizione eventuale di altre costanti
#define SPAZIO 0
#define MESSAGGIO 1
#define MUTEXC 2
#define MUTEXP 3

struct Coda
{
    int buffer[DIM_BUFFER];
    int testa;
    int coda;
};

void produci(struct Coda *, int id_sem, int num_prenotazioni);
int consuma(struct Coda *, int id_sem);

// struttura Count con num_prenotazioni condivisa lato server
typedef struct
{
    // TODO aggiungere variabile per la sincronizzazione
    int num_prenotazioni;
    pthread_mutex_t mutex;
    
} Count;

static inline void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

#endif
