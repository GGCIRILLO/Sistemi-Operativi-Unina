#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include "monitor_signal_continue.h"
#include <stdio.h>
#include <stdlib.h>

#define DIM 4

#define LIBERO 0
#define INUSO 1
#define OCCUPATO1 2
#define OCCUPATO2 3

#define CV_PROD_1 0
#define CV_PROD_2 1
#define CV_CONS_1 2
#define CV_CONS_2 3

typedef struct{

	int vettore[DIM];
	int stato[DIM];

	int num_liberi;
	int num_occupati_tipo1;
	int num_occupati_tipo2;

	//aggiungere ulteriori variabili per la sincronizzazione
	Monitor m;
    
} MonitorPC;

void inizializza(MonitorPC * m);
void rimuovi(MonitorPC * m);
void produci_tipo_1(MonitorPC * m, int valore);
void produci_tipo_2(MonitorPC * m, int valore);
void consuma_tipo_1(MonitorPC * m, int * valore);
void consuma_tipo_2(MonitorPC * m, int * valore);

static inline void die(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

#endif
