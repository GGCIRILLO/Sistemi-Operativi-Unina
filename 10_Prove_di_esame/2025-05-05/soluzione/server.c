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
	pthread_mutex_init(&c->mutex, NULL);
	c->num_prenotazioni = 0;
}

void remove_buffer(Count* c){
	//TODO aggiungere codice per rimuovere Count
	pthread_mutex_destroy(&c->mutex);
}


void *worker(void* arg){

	printf("[WORKER] - start del thread...\n");

	parametri* par = (parametri*) arg /*TODO*/;
	//TODO: completare il passaggio dei parametri
	Count * c = par->count;
	int id = par->id;
	int res;
	
	while (!end) {
		//TODO completare il codice del worker
		// worker preleva dalla coda con funzione "consuma"
		// aggiornamento (eventuale) variabile end se valore ricevuto = -1
		// aggiornamento Count in mutua esclusione	
		res = consuma(coda, ds_sem);
		if (end) break;

		if (res==-1) {
			end = 1;
			printf("[WORKER %d] Ricevuto richiesta di fine\n", id);
			break;
		}
		pthread_mutex_lock(&c->mutex);
			c->num_prenotazioni += res;
			printf("[WORKER %d] Variabile aggiornata %d\n", id, c->num_prenotazioni);
			pthread_mutex_unlock(&c->mutex);
	}
    //TODO uscita dal thread
	pthread_exit(NULL);
}



int main(){

	int i,k;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	//ottenimento e attach shared memory
	key_t key_shm;
	key_shm = ftok(".", 'c') /*TODO*/;
	if (key_shm<0) die("ftok");

	int ds_shm = shmget(key_shm, sizeof(struct Coda), 0) /*TODO*/;
	if (ds_shm<0) die("shmget");

	coda = shmat(ds_shm, NULL, 0) /*TODO*/;
	if (coda==(void*)-1) die("shmat");
	
	//ottenimento array semafori

	key_t key_sem;
	key_sem = ftok(".", 's') /*TODO*/;
	if (key_sem<0) die("ftok");

	ds_sem = semget(key_sem, 3, 0) /*TODO*/;
	if (ds_sem<0);

	//TODO Creazione e Inizializzazione struttura locale
	Count* count = (Count*) malloc(sizeof(Count)) /*TODO*/;
	init_buffer(count);

	parametri param[NUM_WORKER];

	//Avvio dei thread
	for(i = 0; i < NUM_WORKER;i++){
		printf("[SERVER] - creo thread %d...\n",i);
		//TODO creazione threads
		param[i].id = i;
		param[i].count = count;
		pthread_create(&threads[i], &attr, worker, (void*)&param[i]);
	}
	
	for(k=0; k < NUM_WORKER; k++) {
	  //TODO join 
	  pthread_join(threads[k], NULL);
	}
	
	//TODO rimozione struttura locale
	remove_buffer(count);
	free(count);
	
	printf("[SERVER] - bye bye...\n");
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
}

