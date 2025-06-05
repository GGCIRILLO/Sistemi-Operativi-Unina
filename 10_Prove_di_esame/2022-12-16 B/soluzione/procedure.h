#ifndef HEADER_H
#define HEADER_H

#include "monitor_hoare.h"
#include <stdlib.h>
#include <stdio.h>

#define DIM 4

#define MESSAGGIO 1
#define VARCOND_PRODUTTORI 0
#define VARCOND_CONSUMATORI 1

#define N_GENERATORI 3
#define N_FILTRI 3
#define N_STAMPA 3

typedef struct {
	int buffer[DIM];
	
	// TODO: inserire i campi necessari alla gestione della coda circolare
	int testa;
	int coda;
	int count;
	Monitor m;

} MonitorRisultati;


void inserisci_risultato(MonitorRisultati * ls, int valore);
int stampa_risultati(MonitorRisultati * ls);

typedef struct {
	
	// TODO: inserire i campi che costituiscono il messaggio da inviare
	long tipo;
	int valore;
		
} Messaggio;

void filtro(MonitorRisultati * ls, int coda);
void generazione(int coda);
void stampa(MonitorRisultati * ls);

static inline void die(const char* msg){
	perror(msg);
	exit(1);
}

#endif
