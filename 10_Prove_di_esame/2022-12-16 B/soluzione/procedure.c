#include "procedure.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>


int stampa_risultato(MonitorRisultati * ls) {

	int risultato;

	// TODO: consumo il valore
	enter_monitor(&ls->m);

	if (ls->count==0){
		printf("[%d] Sospensione Consumatore\n",getpid());
		wait_condition(&ls->m,VARCOND_CONSUMATORI);
		printf("[%d] Riattivazione Consumatore\n",getpid());
	}

	risultato = ls->buffer[ls->coda];
	ls->coda = (ls->coda+1)%DIM;
	ls->count--;

	signal_condition(&ls->m, VARCOND_PRODUTTORI);

	leave_monitor(&ls->m);

	return risultato;
}


void inserisci_risultato(MonitorRisultati * ls, int valore) {

	// TODO: produco il valore
	enter_monitor(&ls->m);

	if (ls->count==DIM){
		printf("[%d] Sospensione Produttore\n",getpid());
		wait_condition(&ls->m,VARCOND_PRODUTTORI);
		printf("[%d] Riattivazione Produttore\n",getpid());
	}

	ls->buffer[ls->testa] = valore;
	ls->testa = (ls->testa +1)%DIM;
	ls->count++;
	printf("[%d] Inserisco valore: %d\n", getpid(), valore);

	signal_condition(&ls->m, VARCOND_CONSUMATORI);

	leave_monitor(&ls->m);
}

void filtro(MonitorRisultati * ls, int coda){
	Messaggio m;
	int valore = 0;
	for (int i = 0 ; i < 4; i++){
		// TODO: filtro i valori prelevati dalla mailbox: se sono pari, li inserisco, altrimenti inserisco 0
		int ret = msgrcv(coda, (void*)&m, sizeof(m)-sizeof(long), 0, 0);
		if (ret<0) die("msgrcv");
		printf("[%d] Ricevo messaggio con valore %d\n", getpid(), m.valore);
		if (m.valore%2==0){
			valore = m.valore;
		}
		inserisci_risultato(ls, valore);
	}
}
void generazione(int coda) {
	srand(getpid()*time(NULL));
	Messaggio m;
	m.tipo = MESSAGGIO;
	sleep(2);
	for (int i = 0 ; i < 4; i++) {
		
		// TODO: genero dei numeri casuali tra 1 e 20 e li invio alla mailbox
		m.valore = rand()%20+1;
		int ret = msgsnd(coda, (void*)&m, sizeof(m)-sizeof(long), 0);
		if (ret<0) die("msgsnd");
		printf("[%d] Invio messaggio con valore: %d\n", getpid(), m.valore);
	}
}
void stampa(MonitorRisultati * ls) {
	int val;
	for (int i = 0 ; i < 4; i++) {
		
		// TODO: stampo il valore appena consumato
		val = stampa_risultato(ls);
		printf("[%d] Valore consumato: %d\n", getpid(), val);
	}
}
