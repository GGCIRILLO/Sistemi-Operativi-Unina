#ifndef _PRODCONS_
#define _PRODCONS_

#include "monitor_hoare.h"
#include <stdio.h>
#include <stdlib.h>

#define DIM 5

#define LIBER0 0
#define OCCUPATO1 1
#define OCCUAPATO2 2
#define INUSO 3

#define CV_PROD 0
#define CV_CONS 1

typedef struct {

    int buffer[DIM];

    /* TBD: Introdurre ulteriori variabili per la gestione del vettore 
            e per la sincronizzazione */
    int testa;
    int coda;
    int count;

    Monitor m;

} MonitorVettoreCircolare;

void init_monitor_circolare(MonitorVettoreCircolare * p);
void produzione_circolare(MonitorVettoreCircolare * p, int val);
int consumazione_circolare(MonitorVettoreCircolare * p);
void remove_monitor_circolare(MonitorVettoreCircolare * p);

typedef struct {

    int buffer;
    
    /* TBD: Introdurre ulteriori variabili per la gestione del buffer
            e per la sincronizzazione */
    int occupato; // 1 occupato - 0 libero
    Monitor m;

} MonitorBufferSingolo;

void init_monitor_buffer_singolo(MonitorBufferSingolo * b);
void produzione_buffer_singolo(MonitorBufferSingolo * b, int val);
int consumazione_buffer_singolo(MonitorBufferSingolo * b);
void remove_monitor_buffer_singolo(MonitorBufferSingolo * b);

static inline void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

#endif
