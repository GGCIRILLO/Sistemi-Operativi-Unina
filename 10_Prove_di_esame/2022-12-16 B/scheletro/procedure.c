#include "procedure.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>


int stampa_risultato(MonitorRisultati * ls) {

	int risultato;

	// TODO: consumo il valore
			
		
}


void inserisci_risultato(MonitorRisultati * ls, int valore) {

	// TODO: produco il valore
	}

void filtro(MonitorRisultati * ls, int coda){
	Messaggio m;
	int valore = 0;
	for (int i = 0 ; i < 4; i++){
		// TODO: filtro i valori prelevati dalla mailbox: se sono pari, li inserisco, altrimenti inserisco 0
			}
}
void generazione(int coda) {
	srand(getpid()*time(NULL));
	Messaggio m;
	sleep(2);
	for (int i = 0 ; i < 4; i++) {
		
		// TODO: genero dei numeri casuali tra 1 e 20 e li invio alla mailbox
			}
}
void stampa(MonitorRisultati * ls) {
	int val;
	for (int i = 0 ; i < 4; i++) {
		
		// TODO: stampo il valore appena consumato
			}
}
