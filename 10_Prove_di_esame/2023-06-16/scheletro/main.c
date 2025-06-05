#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>

#include "prodcons.h"

void Produttore(MonitorBufferSingolo* b,int id_coda);
void Consumatore(MonitorBufferSingolo* b,int id_coda);

int main() {
	/* TBD: Allocare l'oggetto MonitorBufferSingolo in memoria condivisa */;
    
    /* TBD: Inizializzare l'oggetto MonitorBufferSingolo */


    int id_coda = /* TBD: Allocare una coda di messaggi */

	int pid;
    
    /* TBD: Creare un processo figlio, che esegua la funzione "Consumatore()" */

    /* TBD: Creare un processo figlio, che esegua la funzione "Produttore()" */
    
  
    


 

    /* TBD: Attendere la terminazione dei processi figli */


    /* TBD: Deallocare l'oggetto monitor */

    /* TBD: Deallocare la coda di messaggi */
}


void Produttore(MonitorBufferSingolo* b,int id_coda) {

    int numero_elementi = rand() % 10;

    printf("[%d][PRODUTTORE] Totale elementi da inviare: %d\n",getpid(),numero_elementi);

    /* TBD: Effettuare una produzione su MonitorBufferSingolo con
            la funzione "produzione_buffer_singolo", inserendo "numero_elementi"
     */
    

    for(int i=0; i<numero_elementi; i++) {
    
        sleep(1);

        int val = rand() % 10;

        printf("[%d] [PRODUTTORE] Invio del valore: %d\n", getpid(),val);

		messaggio m;
		m.tipo = MESSAGGIO;
		m.valore = val;
        /* TBD: Inviare il valore "val" tramite la coda di messaggi */

    }
}

void Consumatore(MonitorBufferSingolo* b,int id_coda) {

    /* TBD: Effettuare una consumazione su MonitorBufferSingolo con
            la funzione "consumazione_buffer_singolo", prelevando "numero_elementi"
     */

    


    for(int i=0; i<numero_elementi; i++) {

        /* TBD: Ricevere il valore "val" tramite la coda di messaggi */

        int val =  /* TBD */;

        printf("[%d][CONSUMATORE] Ricezione del valore: %d\n", getpid(),val);
    }
}
