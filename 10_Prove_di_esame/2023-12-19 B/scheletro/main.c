#include "prodcons.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void * Produttore(void *);
void * Consumatore(void *);

int main() {

    /* TBD: Avviare i thread produttore e consumatore */
	//Creazione oggetto MonitorStreaming
	
	//Inizializzazione m
	
	//Creazione thread
	pthread_t produttore;
	pthread_t consumatore;
	
	//Avvio dei thread
	
	
	//Terminazione dei thread

	
	//distruzione mutex e de-allocazione memoria
	

}

void * Produttore(void * p) {
	
	MonitorStreaming * m = (MonitorStreaming *) p;

    for(int i=0; i<10; i++) {
		
		//printf("Inizio produttore #%d \n",i);

        Frame f;
        f[0][0] = rand() % 11;
        f[0][1] = rand() % 11;
        f[1][0] = rand() % 11;
        f[1][1] = rand() % 11;

        /* TBD: Chiamare il metodo "produci()" del monitor */
		

        sleep(1);
    }

    pthread_exit(NULL);
}

void * Consumatore(void * p) {
	
	MonitorStreaming * m = (MonitorStreaming *) p;

    /* TBD: Chiamare il metodo "bufferizza()" del monitor */
	int n = 4;
	

    for(int i=0; i<10; i++) {
		
		//printf("Inizio consumatore #%d \n",i);

        Frame f;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
		

        sleep(1);
    }

    pthread_exit(NULL);
}