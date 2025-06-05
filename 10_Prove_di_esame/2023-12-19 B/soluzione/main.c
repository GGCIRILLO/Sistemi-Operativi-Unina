#include "prodcons.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void * Produttore(void *);
void * Consumatore(void *);

int main() {

    /* TBD: Avviare i thread produttore e consumatore */
	//Creazione oggetto MonitorStreaming
	
	MonitorStreaming * m = malloc(sizeof(MonitorStreaming));
	
	//Inizializzazione m
	inizializza(m);
	
	//Creazione thread
	pthread_t produttore;
	pthread_t consumatore;

	//Avvio dei thread
	pthread_create(&produttore,NULL,Produttore,m);
	
	pthread_create(&consumatore,NULL,Consumatore,m);
	
	//Terminazione dei thread
	pthread_join(produttore,NULL);
	pthread_join(consumatore,NULL);
	
	//distruzione mutex e de-allocazione memoria
	distruggi(m);
	free(m);
	

}

void * Produttore(void * p) {
	
	MonitorStreaming * m = (MonitorStreaming *) p;

    for(int i=0; i<10; i++) {
		
		printf("Inizio produttore #%d \n",i+1);

        Frame f;
        f[0][0] = rand() % 11;
        f[0][1] = rand() % 11;
        f[1][0] = rand() % 11;
        f[1][1] = rand() % 11;

        /* TBD: Chiamare il metodo "produci()" del monitor */
		produci(m,f);

        sleep(1);
    }

    pthread_exit(NULL);
}

void * Consumatore(void * p) {
	
	MonitorStreaming * m = (MonitorStreaming *) p;

    /* TBD: Chiamare il metodo "bufferizza()" del monitor */
	
	bufferizza(m, N);

    for(int i=0; i<10; i++) {
		
		printf("Inizio consumatore #%d \n",i+1);

        Frame f;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
		consuma(m, f);

        sleep(1);
    }

    pthread_exit(NULL);
}