#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"

void produttore(struct prodcons * p, int ds_sem) {

    // TODO: Attendere che ci sia spazio disponibile nel buffer (Wait su SPAZIO_DISPONIBILE)
	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);

    // TODO: Entrare in sezione critica per la scrittura (Wait su MUTEX_P)
	Wait_Sem(ds_sem, MUTEX_P);

	sleep(2);

    // TODO: Generare un valore casuale e inserirlo nella posizione "testa" del buffer
	p->buffer[p->testa] = rand() % 100;
	printf("Valore generato: %d\n", p->buffer[p->testa]);

    // TODO: Aggiornare l’indice "testa" con politica circolare
	p->testa = (p->testa +1) % DIM_BUFFER;

    // TODO: Uscire dalla sezione critica (Signal su MUTEX_P)
	Signal_Sem(ds_sem, MUTEX_P);

    // TODO: Segnalare che un nuovo messaggio è disponibile (Signal su MESSAGGIO_DISPONIBILE)
	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(struct prodcons * p, int ds_sem) {

    // TODO: Attendere che ci sia almeno un messaggio da consumare (Wait su MESSAGGIO_DISPONIBILE)
	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);

    // TODO: Entrare in sezione critica per la lettura (Wait su MUTEX_C)
	Wait_Sem(ds_sem, MUTEX_C);

    sleep(2);

    // TODO: Leggere il valore dalla posizione "coda" del buffer
	int coda = p->buffer[p->coda];
	printf("Valore consumato: %d\n", coda);

    // TODO: Aggiornare l’indice "coda" con politica circolare
	p->coda = (p->coda +1)%DIM_BUFFER;

    // TODO: Uscire dalla sezione critica (Signal su MUTEX_C)
	Signal_Sem(ds_sem, MUTEX_C);

    // TODO: Segnalare che c'è di nuovo spazio disponibile nel buffer (Signal su SPAZIO_DISPONIBILE)
	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}