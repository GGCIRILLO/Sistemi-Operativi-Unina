#ifndef _HEADER_
#define _HEADER_

#include "monitor_signal_continue.h"
#include <stdlib.h>
#include <stdio.h>

#define DIM 3

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define CV_PROD 0
#define CV_CONS 1

typedef struct {

    int buffer[DIM];

    int ultimo_produttore_arrivato;
    int ultimo_produttore_avviato;

    /* TBD: Aggiungere ulteriori variabili per la sincronizzazione */
    int num_liberi;
    int num_occupati;

    int stato[DIM];

    Monitor m;

} MonitorProdConsFIFO;

void inizializza(MonitorProdConsFIFO * p);
void produci(MonitorProdConsFIFO * p, int valore);
int consuma(MonitorProdConsFIFO * p);
void distruggi(MonitorProdConsFIFO * p);

static inline void die(const char * msg){
    perror(msg);
    exit(1);
}

#endif