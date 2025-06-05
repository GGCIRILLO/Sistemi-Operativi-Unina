#include "header.h"
#include <pthread.h>

void inizializza(struct monitor* m){

    // TODO: inizializza variabile di supporto per rate limiting e buffer circolare
    m->n_mex_lastsec = 0;
    m->testa=0;
    m->coda = 0;
    m->count=0;

    // TODO: inizializza mutex e cv necessarie
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cv_prod, NULL);
    pthread_cond_init(&m->cv_cons, NULL);
}

void rimuovi (struct monitor* m){
    // TODO: rimuovi strutture inizializzate
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->cv_prod);
    pthread_cond_destroy(&m->cv_cons);
}

void send_coordinates(struct monitor* m, struct coordinates* c){
    //TODO: entra nel monitor e deposita le coordinate se si è sotto al limite di messaggi al secondo
    pthread_mutex_lock(&m->mutex);

    while (m->n_mex_lastsec >= REQUEST_RATE || m->count >= NELEM_MONITOR){
        pthread_cond_wait(&m->cv_prod, &m->mutex);
    }
    m->buffer[m->testa] = *c;
    m->testa = (m->testa+1)%NELEM_MONITOR;
    m->count++;
    m->n_mex_lastsec++;

    pthread_cond_signal(&m->cv_cons);

    pthread_mutex_unlock(&m->mutex);
}

void receive_coordinates(struct monitor* m, struct coordinates* c){
    //TODO: entra nel monitor e consuma
    pthread_mutex_lock(&m->mutex);

    while(m->count == 0){
        pthread_cond_wait(&m->cv_cons, &m->mutex);
    }

    *c = m->buffer[m->coda];
    m->coda=(m->coda+1)%NELEM_MONITOR;
    m->count--;

    pthread_cond_signal(&m->cv_prod);

    pthread_mutex_unlock(&m->mutex);
}

void reset_rate(struct monitor* m){
    //TODO: reset rate
    pthread_mutex_lock(&m->mutex);

    m->n_mex_lastsec = 0;

    pthread_cond_broadcast(&m->cv_prod);

    pthread_mutex_unlock(&m->mutex);
}





