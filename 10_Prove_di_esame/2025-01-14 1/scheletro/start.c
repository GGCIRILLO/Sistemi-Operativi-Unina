#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#include "monitor_fifo.h"

#define PROCESSI_PRODUTTORI 5
#define PROCESSI_CONSUMATORI 2

#define NUMERO_PRODUZIONI 4
#define NUMERO_CONSUMAZIONI 10

void consumatore(MonitorProdConsFIFO * p);
void produttore(MonitorProdConsFIFO * p);

int main() {

    /* TBD: Creare l'oggetto monitor, utilizzando la funzione "inizializza()" */

    /* TBD: Avviare i processi produttori, facendogli eseguire la funzione "produttore()"
            e i processi consumatori, facendogli eseguire la funzione "consumatore()"
     */

    /* TBD: Rimuovere l'oggetto monitor, utilizzando la funzione "distruggi()" */
}


void produttore(MonitorProdConsFIFO * p) {

    srand(getpid());

    for(int i=0; i<NUMERO_PRODUZIONI; i++) {

        int valore = rand() % 100;

        printf("[PRODUTTORE %d] Produzione valore %d\n", getpid(), valore);

        /* TBD: Chiamare la funzione "produci()" del monitor */

    }

}

void consumatore(MonitorProdConsFIFO * p) {

    for(int i=0; i<NUMERO_CONSUMAZIONI; i++) {

        printf("[CONSUMATORE %d] Inizio consumazione\n", getpid());

        int valore;

        /* TBD: Chiamare la funzione "consuma()" del monitor */

        printf("[CONSUMATORE %d] Consumazione valore %d\n", getpid(), valore);
    }

}