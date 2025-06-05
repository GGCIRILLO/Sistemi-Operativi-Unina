#include "header.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>

void * create_coordinates (void * p){
	struct coordinates c;
	// TODO: ottenimento parametri passati: monitor e coordinata x
	printf("[Create: Started create_coordinates, randint: %d]\n",par->x);
	
	sleep(1);
	for(int i=0; i<N_COMPUTE_PER_THREAD; i++){
		c.y = rand()%100;
		printf("[Create: Created coordinates: %d, %d]\n",c.x, c.y);
		// TODO: inserimento delle coordinate nel monitor
		sleep(1);
	}
	// TODO: terminazione thread
}

void * send_values (void * p){
	// TODO: creazione coda di messaggi

	// TODO: ottenimento parametri passati: monitor
	printf("[Send: Started send_values]\n");
	struct coordinates c;

	sleep(1);
	for(int i=0; i<N_COMPUTE_PER_THREAD*NTHREADS_PROD; i++){
		// TODO: Consuma coordinate prese dal monitor
		printf("[Consumed coordinates: %d, %d]\n",c.x, c.y);
		// TODO: creazione e invio messaggio sulla coda
	}

	// TODO: rimozione coda
	// TODO: terminazione thread
}

void * rate_limiter_loop (void * p){
	// TODO: ottenimento parametri passati: monitor
	printf("[Create: Started rate_limiter]\n");

	for(int i=0; i<15; i++){
		// TODO: reset rate limiting del monitor 
		printf("\t\t[Resetting limits]\n");
		sleep(1);
	}
	// TODO: terminazione thread
}

int main() {

	srand(time(NULL));

	// TODO: Creazione attributi task

	// TODO: Creazione variabili necessarie per pthreads

	// TODO: Creazione struttura per passaggio parametri a thread

	// TODO: Allocazione monitor

	int i;

	// TODO: creazione thread rate_limiter

	sleep(1);

	
	for(i=0;i<NTHREADS_PROD;i++){
		// TODO: riempimento parametri threads (inclusa la coordinata x)
		// TODO: creazione thread produttore
	}

	// TODO: creazione thread consumatore

	for(i=0;i<NTHREADS_PROD;i++){
		// TODO: attesa thread produttore
		printf("Producer %d terminato\n",i+1);
	}

	// TODO: attesa altri thread
	printf("Consumer terminato\n");
	printf("Rate limiter terminato\n");

	// TODO: rimozione monitor
	return 0;
}	
