#include "header.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <pthread.h>


void * create_coordinates (void * p){
	struct coordinates c;
	// TODO: ottenimento parametri passati: monitor e coordinata x
	struct parameters * par = (struct parameters*) p;
	struct monitor * m = par->m;
	c.x = par->x;
	printf("[Create: Started create_coordinates, randint: %d]\n",par->x);
	
	sleep(1);
	for(int i=0; i<N_COMPUTE_PER_THREAD; i++){
		c.y = rand()%100;
		printf("[Create: Created coordinates: %d, %d]\n",c.x, c.y);
		// TODO: inserimento delle coordinate nel monitor
		send_coordinates(m, &c);
		sleep(1);
	}
	// TODO: terminazione thread
	pthread_exit(NULL);
}

void * send_values (void * p){
	// TODO: creazione coda di messaggi
	key_t k_q = ftok(".", 'q');
	int id_coda = msgget(k_q, IPC_CREAT|0664);

	// TODO: ottenimento parametri passati: monitor
	struct monitor * m = (struct monitor*)p;
	printf("[Send: Started send_values]\n");
	struct coordinates c;

	sleep(1);
	for(int i=0; i<N_COMPUTE_PER_THREAD*NTHREADS_PROD; i++){
		// TODO: Consuma coordinate prese dal monitor
		receive_coordinates(m, &c);

		printf("[Consumed coordinates: %d, %d]\n",c.x, c.y);
		// TODO: creazione e invio messaggio sulla coda
		struct message msg;
		msg.tipo = 1;
		msg.coords = c;
		msgsnd(id_coda, (void*)&msg, sizeof(msg)-sizeof(long), 0);
	}

	// TODO: rimozione coda
	msgctl(id_coda, IPC_RMID, NULL);
	// TODO: terminazione thread
	pthread_exit(NULL);
}

void * rate_limiter_loop (void * p){
	// TODO: ottenimento parametri passati: monitor
	struct monitor * m = (struct monitor*) p; 
	printf("[Create: Started rate_limiter]\n");

	for(int i=0; i<15; i++){
		// TODO: reset rate limiting del monitor 
		reset_rate(m);
		printf("\t\t[Resetting limits]\n");
		sleep(1);
	}
	// TODO: terminazione thread
	pthread_exit(NULL);
}

int main() {

	srand(time(NULL));

	// TODO: Creazione attributi task
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	// TODO: Creazione variabili necessarie per pthreads
	pthread_t prod_threads[NTHREADS_PROD];
	pthread_t cons_thread;
	pthread_t rl_thread;

	// TODO: Creazione struttura per passaggio parametri a thread
	struct parameters params[NTHREADS_PROD];

	// TODO: Allocazione monitor
	struct monitor* m = malloc(sizeof(struct monitor));
	inizializza(m);

	int i;

	// TODO: creazione thread rate_limiter
	pthread_create(&rl_thread, &attr, rate_limiter_loop, (void*)m);

	sleep(1);

	
	for(i=0;i<NTHREADS_PROD;i++){
		// TODO: riempimento parametri threads (inclusa la coordinata x)
		params[i].m = m;
		params[i].x = rand() % 100;
		// TODO: creazione thread produttore
		pthread_create(&prod_threads[i], &attr, create_coordinates, (void*)&params[i]);
	}

	// TODO: creazione thread consumatore
	pthread_create(&cons_thread, &attr, send_values, (void*)m);

	for(i=0;i<NTHREADS_PROD;i++){
		// TODO: attesa thread produttore
		pthread_join(prod_threads[i], NULL);
		printf("Producer %d terminato\n",i+1);
	}

	// TODO: attesa altri thread
	pthread_join(cons_thread, NULL);
	printf("Consumer terminato\n");

	pthread_join(rl_thread, NULL);
	printf("Rate limiter terminato\n");

	// TODO: rimozione monitor
	rimuovi(m);
	free(m);

	return 0;
}	
