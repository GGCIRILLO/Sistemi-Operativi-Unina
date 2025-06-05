#ifndef HEADER_H
#define HEADER_H

#include "monitor_hoare.h"

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
	} MonitorRisultati;


void inserisci_risultato(MonitorRisultati * ls, int valore);
int stampa_risultati(MonitorRisultati * ls);

typedef struct {
	
	// TODO: inserire i campi che costituiscono il messaggio da inviare
		
} Messaggio;

void filtro(MonitorRisultati * ls, int coda);
void generazione(int coda);
void stampa(MonitorRisultati * ls);

#endif
