#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "header.h"

#define NUM_WORKER 3

static int coda;
static pthread_t threads[NUM_WORKER+1];


// struttura per il passaggio dei parametri ai thread worker
typedef struct {
	int id;
	Buffer* b;
} parametri;

void init_buffer(Buffer* b){
	//TODO inizializzazione del buffer

	b->somma = 0;
	b->count=0;

	pthread_mutex_init(&b->mutex, NULL);
	pthread_cond_init(&b->cv_worker, NULL);
	pthread_cond_init(&b->cv_collector, NULL);

	printf("[SERVER] - Buffer inizializzato...\n");
}

void remove_buffer(Buffer* b){
	//TODO distruzione delle variabili de buffer
	pthread_mutex_destroy(&b->mutex);
	pthread_cond_destroy(&b->cv_worker);
	pthread_cond_destroy(&b->cv_collector);
	
	printf("[SERVER] - Buffer distrutto...\n");
}


void aggiorna_somma(Buffer* b, int somma_parziale){
	// TODO aggiungere la somma parziale alla somma nel buffer,
	//		risvegliando il prelievo della somma finale quando necessario...
	pthread_mutex_lock(&b->mutex);

	while (b->count>=NUM_WORKER*NUM_REQ){
		pthread_cond_wait(&b->cv_worker, &b->mutex);
	}

	b->somma += somma_parziale;
	b->count ++;

	if (b->count==NUM_WORKER*NUM_REQ){
		pthread_cond_signal(&b->cv_collector);
	}

	
	pthread_mutex_unlock(&b->mutex);

}

int preleva_somma_finale(Buffer* b){
	int somma_finale;
	//TODO prelevare la somma finale dal buffer, 
	// 		solo quando sono state accumulati NUM_WORKER*NUM_REQ incrementi
	pthread_mutex_lock(&b->mutex);

	while(b->count<30){
		pthread_cond_wait(&b->cv_collector, &b->mutex);
	}

	somma_finale = b->somma;
	b->count = 0;

	pthread_cond_signal(&b->cv_worker);

	pthread_mutex_unlock(&b->mutex);

	return somma_finale;
}

void* collector(void* arg){
	int somma_finale;
	float media;

	// TODO recupera l'argomento
	Buffer * b = (Buffer*) arg;

	printf("[COLLECTOR] - start del thread...\n");

	// TODO preleva la somma chiamando preleva_somma_finale
	somma_finale = preleva_somma_finale(b);
	
	media = (float) somma_finale/(NUM_REQ*NUM_WORKER); //TODO calcola la media sul totale delle misure ricevute
	
	printf("[COLLECTOR] - somma finale: %d media: %f\n",somma_finale,media);
	
}

void *worker(void* arg){

	printf("[WORKER] - start del thread...\n");

	//TODO recupera i parametri
	parametri* p = (parametri*) arg;
	
	Misura m;
	
	//TODO ogni worker preleva NUM_REQ messaggi relativi ad un certo client id 
	//     e per ogni messaggio ricevuto aggiorna la somma chiamando aggiorna_somma
	for (int i=0;i<NUM_REQ;i++){
		if (msgrcv(coda, (void*)&m, sizeof(m)-sizeof(long), p->id, 0)<0) die("msgrcv");

		 printf("[WORKER] - Ho ricevuto la misura %d dal sensore %ld \n",m.valore,m.id_client);

		aggiorna_somma(p->b, m.valore);
	}

	printf("[WORKER-DEBUG] Somma parziale: %d\n", p->b->somma);

}



int main(){

	int i,status;
	pid_t pid;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	key_t key;
	key = ftok(".", 'q'); //TODO:inserire la chiave
    
	coda = msgget(key, 0664); //TODO:inizializzare la coda

	printf("[SERVER] - id coda %d\n",coda);


	//Inizializziamo strutture
	
	Buffer* b = (Buffer*) malloc(sizeof(Buffer)); //...

	init_buffer(b);

	parametri params[NUM_WORKER];
	
	
	//Avvio dei thread
	for(i = 0; i < NUM_WORKER+1;i++){

		printf("[MASTER] - creo thread %d...\n",i);

		// TODO creazione di 1 trhead collector e 3 thread worker (ai quali passare anche l'id)
		if (i==0){
			pthread_create(&threads[i], &attr, collector, (void*)b );
		} else{
			params[i].id=i;
			params[i].b=b;
			pthread_create(&threads[i], &attr, worker, (void*)&params[i]);
		}
		
	}

	printf("[MASTER] - bye bye...\n");
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);

	remove_buffer(b);
	free(b);

    return 0;
}

