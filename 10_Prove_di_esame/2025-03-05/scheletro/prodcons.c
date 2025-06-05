#include "header_prodcons.h"

void buffer_init(struct buffer * b) {

    /* TBD: Inizializzare la struttura dati */
}

void buffer_produci(struct buffer * b, int valore) {

    /* TBD: Completare la sincronizzazione */

    b->valore = valore;

    pthread_cond_signal(&b->cv_cons);

    pthread_mutex_unlock(&b->mutex);
}

int buffer_consuma(struct buffer * b) {

    int valore;

    /* TBD: Completare la sincronizzazione */

    valore = b->valore;

    return valore;
}

void buffer_destroy(struct buffer * b) {

    /* TBD: De-inizializzare le variabili per la sincronizzazione */
}
