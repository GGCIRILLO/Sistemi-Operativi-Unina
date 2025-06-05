#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <pthread.h>
#include "header.h"

#define NUM_WORKER 3

static struct Coda * coda;
static int ds_sem;
static pthread_t threads[NUM_WORKER];
static int end = 0;

// struttura per passaggio parametri ai thread
typedef struct {
	int id;
	Count* count;
} parametri;

void init_buffer(Count* c){
	//TODO aggiungere codice per inizializzare Count
}

void remove_buffer(Count* c){
	//TODO aggiungere codice per rimuovere Count
}


void *worker(void* arg){

	printf("[WORKER] - start del thread...\n");

	parametri* par = /*TODO*/;
	//TODO: completare il passaggio dei parametri
	
	while (!end) {
		//TODO completare il codice del worker
		// worker preleva dalla coda con funzione "consuma"
		// aggiornamento (eventuale) variabile end se valore ricevuto = -1
		// aggiornamento Count in mutua esclusione	
	}
    //TODO uscita dal thread
}



int main(){

	int i,k;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	//ottenimento e attach shared memory
	key_t key_shm;
	key_shm = /*TODO*/;

	int ds_shm = /*TODO*/;

	coda = /*TODO*/;
	
	//ottenimento semafori

	key_t key_sem;
	key_sem = /*TODO*/;

	ds_sem = /*TODO*/;

	//TODO Creazione e Inizializzazione struttura locale
	Count* count = /*TODO*/;
	
	parametri param[NUM_WORKER];

	//Avvio dei thread
	for(i = 0; i < NUM_WORKER;i++){
		printf("[SERVER] - creo thread %d...\n",i);
		//TODO creazione threads	
	}
	
	for(k=0; k < NUM_WORKER; k++) {
	  //TODO join 
	}
	
	//TODO rimozione struttura locale
	printf("[SERVER] - bye bye...\n");
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
}

