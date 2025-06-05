#ifndef _PRODCONS_
#define _PRODCONS_

#include <pthread.h>

#define DIM 5

typedef struct {

    int buffer[DIM];

    int conteggio_consumazioni;    /* conteggio consumazioni effettuate */

    /* TBD: Aggiungere ulteriori variabili per la 
            gestione del vettore di buffer circolare
            e per la sincronizzazione
     */

} MonitorProdCons;


void init_monitor(MonitorProdCons * p);
void produzione(MonitorProdCons * p, int val);
int consumazione(MonitorProdCons * p);
int attendi_consumazioni(MonitorProdCons * p, int soglia);
void remove_monitor(MonitorProdCons * p);

#endif