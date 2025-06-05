#ifndef _HEADER_H_
#define _HEADER_H_

#include "monitor_hoare.h"

#define NUM_PRODUTTORI 6
#define NUM_CONSUMATORI 2

#define DIMENSIONE 5

/* TBD: Aggiungere macro per la gestione delle variabili condition e del vettore di stato */
#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define CV_PROD 0
#define CV_CONS 1

typedef struct {

    int vettore[DIMENSIONE];
    
    /* TBD: Aggiungere variabili per la sincronizzazione */
    int stato[DIMENSIONE];
    int produttori_in_attesa;
    int num_liberi;
    int num_occupati;

    Monitor m;
    
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
