#include "header_prodcons.h"

void buffer_init(struct buffer * b) {

    /* TBD: Inizializzare la struttura dati */
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cv_cons, NULL);
    pthread_cond_init(&b->cv_prod, NULL);
    b->libero = 1;
}

void buffer_produci(struct buffer * b, int valore) {

    /* TBD: Completare la sincronizzazione */
    pthread_mutex_lock(&b->mutex);

    while (b->libero==0){ // occupato
        pthread_cond_wait(&b->cv_prod, &b->mutex);
    }

    b->valore = valore;
    b->libero = 0;

    pthread_cond_signal(&b->cv_cons);

    pthread_mutex_unlock(&b->mutex);
}

int buffer_consuma(struct buffer * b) {

    int valore;

    /* TBD: Completare la sincronizzazione */
    pthread_mutex_lock(&b->mutex);

    while (b->libero==1){ // libero
        pthread_cond_wait(&b->cv_cons, &b->mutex);
    }

    valore = b->valore;
    b->libero = 1;

    pthread_cond_signal(&b->cv_prod);

    pthread_mutex_unlock(&b->mutex);

    return valore;
}

void buffer_destroy(struct buffer * b) {

    /* TBD: De-inizializzare le variabili per la sincronizzazione */
    pthread_mutex_destroy(&b->mutex);
    pthread_cond_destroy(&b->cv_cons);
    pthread_cond_destroy(&b->cv_prod);
}
