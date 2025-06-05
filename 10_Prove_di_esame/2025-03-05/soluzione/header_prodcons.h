#ifndef _HEADER_PRODCONS
#define _HEADER_PRODCONS

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

struct buffer {
    
    int valore;

    /* TBD: Aggiungere altre variabili per la sincronizzazione */
    int libero; // 1 libero; 0 occupato;
    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;
};

void buffer_init(struct buffer * b);
void buffer_produci(struct buffer * b, int valore);
int buffer_consuma(struct buffer * b);
void buffer_destroy(struct buffer * b);

static inline void die(const char * msg){
    perror(msg);
    exit(1);
}

#endif