#ifndef _HEADER_H_
#define _HEADER_H_

#include "monitor_hoare.h"

#define NUM_PRODUTTORI 6
#define NUM_CONSUMATORI 2

#define DIMENSIONE 5

/* TBD: Aggiungere macro per la gestione delle variabili condition e del vettore di stato */

typedef struct {

    int vettore[DIMENSIONE];
    
    /* TBD: Aggiungere variabili per la sincronizzazione */
	

    
} MonitorCoda;

// il valore di ritorno di produzione() indica se il monitor è sovraccarico
int produzione(MonitorCoda *m, int valore);

// il valore di ritorno di consumazione() è il valore prelevato dalla coda
int consumazione(MonitorCoda *m);

void produttore(MonitorCoda *m);
void consumatore(MonitorCoda *m);

void inizializza(MonitorCoda *m);
void rimuovi(MonitorCoda * p);

#endif
