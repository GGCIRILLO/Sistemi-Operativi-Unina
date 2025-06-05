#ifndef _HEADER_PRODCONS_H_
#define _HEADER_PRODCONS_H_

#include <pthread.h>

typedef struct {

    /* TBD: Aggiungere ulteriori variabili per la sincronizzazione */

    int valore;
    int stato;

    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;

} BufferProdCons;

#define VUOTO 0
#define PIENO 1

void produci_valore(BufferProdCons * b, int valore);
int consuma_valore(BufferProdCons * b);
void * visualizza(void *);

#endif