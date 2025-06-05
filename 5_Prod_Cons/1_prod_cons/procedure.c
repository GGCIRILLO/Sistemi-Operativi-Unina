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

void produttore(int * p, int ds_sem) {

	printf("produttore è fermo prima di wait\n");
	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);  // Attende che ci sia spazio disponibile nel buffer
	printf("produttore si sblocca dopo la wait\n");

	sleep(2);  // Simula tempo impiegato per produrre

	*p = rand() % 100;  // Scrive un valore casuale nella memoria condivisa

	printf("Il valore prodotto = %d\n", *p);

	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);  // Segnala che è disponibile un nuovo messaggio
}

void consumatore(int * p, int ds_sem) {

	printf("consumatore è fermo prima di wait\n");
	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);  // Attende che ci sia un messaggio da consumare
	printf("consumatore si sblocca dopo la wait\n");

	sleep(2);  // Simula tempo impiegato per consumare

	printf("Il valore consumato = %d\n", *p);  // Legge e stampa il valore dalla SHM

	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);  // Segnala che c'è di nuovo spazio nel buffer
}