#include <stdio.h>

#include "prodcons.h"


void init_monitor(MonitorProdCons * p) {

    /* TBD: Inizializzare l'oggetto monitor */

    p->conteggio_consumazioni = 0;

    p->testa = 0;
    p->coda=0;
    p->elementi=0;

    pthread_mutex_init(&p->mutex, NULL);
    pthread_cond_init(&p->cv_prod, NULL );
    pthread_cond_init(&p->cv_cons, NULL);
    pthread_cond_init(&p->cv_conteggio, NULL);
}

void produzione(MonitorProdCons * p, int val) {

    /* TBD: Completare la sincronizzazione, in base allo schema
            del vettore di buffer circolare */

    pthread_mutex_lock(&p->mutex);

    while(p->elementi==DIM){
        pthread_cond_wait(&p->cv_prod, &p->mutex);
    }
    p->buffer[p->testa/*TBD*/] = val;
    p->testa = (p->testa+1)%DIM;
    p->elementi++;

    pthread_cond_signal(&p->cv_cons);

    pthread_mutex_unlock(&p->mutex);

}

int consumazione(MonitorProdCons * p) {

    int val;

    /* TBD: Completare la sincronizzazione, in base allo schema
            del vettore di buffer circolare */

    pthread_mutex_lock(&p->mutex);

    while(p->elementi==0){
        pthread_cond_wait(&p->cv_cons, &p->mutex);
    }

    val = p->buffer[p->coda/*TBD*/];
    p->coda = (p->coda+1)%DIM;
    p->elementi--;

    p->conteggio_consumazioni++;

    pthread_cond_signal(&p->cv_conteggio);
    pthread_cond_signal(&p->cv_prod);

    pthread_mutex_unlock(&p->mutex);

    return val;
}

int attendi_consumazioni(MonitorProdCons * p, int soglia) {

    int n;

    /* TBD: Sospendere il thread finché il "conteggio_consumazioni" non sia diventato
            maggiore o uguale a "soglia"
     */

    pthread_mutex_lock(&p->mutex);

    while(p->conteggio_consumazioni<soglia){
        pthread_cond_wait(&p->cv_conteggio, &p->mutex);
    }

    n = p->conteggio_consumazioni;

    p->conteggio_consumazioni = 0;

    pthread_mutex_unlock(&p->mutex);
    
    return n;
}

void remove_monitor(MonitorProdCons * p) {

    /* TBD: Disattivare le variabili per la sincronizzazione */
    pthread_mutex_destroy(&p->mutex);
    pthread_cond_destroy(&p->cv_prod);
    pthread_cond_destroy(&p->cv_cons);
    pthread_cond_destroy(&p->cv_conteggio);
}