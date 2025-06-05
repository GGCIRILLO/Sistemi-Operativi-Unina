#ifndef _HEADER_PRODCONS
#define _HEADER_PRODCONS

#include <pthread.h>

struct buffer {
    
    int valore;

    /* TBD: Aggiungere altre variabili per la sincronizzazione */
};

void buffer_init(struct buffer * b);
void buffer_produci(struct buffer * b, int valore);
int buffer_consuma(struct buffer * b);
void buffer_destroy(struct buffer * b);

#endif