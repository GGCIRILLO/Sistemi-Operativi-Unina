#ifndef _PRODCONS_
#define _PRODCONS_

#include "monitor_hoare.h"

#define DIM 5

#define LIBER0 0
#define OCCUPATO1 1
#define OCCUAPATO2 2
#define INUSO 3

typedef struct {

    int buffer[DIM];

    /* TBD: Introdurre ulteriori variabili per la gestione del vettore 
            e per la sincronizzazione */



} MonitorVettoreCircolare;

void init_monitor_circolare(MonitorVettoreCircolare * p);
void produzione_circolare(MonitorVettoreCircolare * p, int val);
int consumazione_circolare(MonitorVettoreCircolare * p);
void remove_monitor_circolare(MonitorVettoreCircolare * p);

typedef struct {

    int buffer;
    
    /* TBD: Introdurre ulteriori variabili per la gestione del buffer
            e per la sincronizzazione */


} MonitorBufferSingolo;

void init_monitor_buffer_singolo(MonitorBufferSingolo * b);
void produzione_buffer_singolo(MonitorBufferSingolo * b, int val);
int consumazione_buffer_singolo(MonitorBufferSingolo * b);
void remove_monitor_buffer_singolo(MonitorBufferSingolo * b);

#endif
