#ifndef _PRODCONS_
#define _PRODCONS_

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM 5

typedef struct {

    int buffer[DIM];

    int conteggio_consumazioni;    /* conteggio consumazioni effettuate */

    /* TBD: Aggiungere ulteriori variabili per la 
            gestione del vettore di buffer circolare
            e per la sincronizzazione
     */
    int testa;
    int coda;
    int elementi;

    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;
    pthread_cond_t cv_conteggio;

} MonitorProdCons;


void init_monitor(MonitorProdCons * p);
void produzione(MonitorProdCons * p, int val);
int consumazione(MonitorProdCons * p);
int attendi_consumazioni(MonitorProdCons * p, int soglia);
void remove_monitor(MonitorProdCons * p);

static inline void die(const char*x){
    perror(x);
    exit(1);
}

#endif