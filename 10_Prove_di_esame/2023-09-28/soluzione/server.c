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

static struct Coda *coda;
static int ds_sem;
static pthread_t threads[NUM_WORKER];
static int end = 0;

// struttura per passaggio parametri ai thread
typedef struct
{
	int id;
	Count *count;
} parametri;

void init_buffer(Count *c)
{
	// TODO aggiungere codice per inizializzare Count
	c->num_prenotazioni = 0;
	pthread_mutex_init(&c->mutex, NULL);
}

void remove_buffer(Count *c)
{
	// TODO aggiungere codice per rimuovere Count
	pthread_mutex_destroy(&c->mutex);
	free(c);
}

void *worker(void *arg)
{
	parametri *par = (parametri*)arg /*TODO*/;
	// TODO: completare il passaggio dei parametri
	Count *count = par->count;
	int id = par->id;

	printf("[WORKER %d] - Inizio del thread...\n", id);
	while (!end)
	{
		// TODO completare il codice del worker
		//  worker preleva dalla coda con funzione "consuma"
		//  aggiornamento (eventuale) variabile end se valore ricevuto = -1
		//  aggiornamento Count in mutua esclusione
		int num_prenotazioni = consuma(coda, ds_sem);
		if (num_prenotazioni == -1)
		{
			end = 1; // segnale di terminazione
			printf("[WORKER %d] - Ricevuta richiesta di terminazione\n", id);
			break;
		}
		printf("[WORKER %d] - Consumo prenotazioni: %d\n", id, num_prenotazioni);
		pthread_mutex_lock(&count->mutex);
		count->num_prenotazioni += num_prenotazioni;
		pthread_mutex_unlock(&count->mutex);
		printf("[WORKER %d] - Prenotazioni totali: %d\n", id, count->num_prenotazioni);
	}
	// TODO uscita dal thread
	printf("[WORKER %d] - Fine del thread...\n", id);
	pthread_exit(NULL);
}

int main()
{

	int i, k;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	key_t key_shm;
	key_shm = ftok(".", 'a') /*TODO*/;
	if (key_shm == -1)
		die("ftok");

	int ds_shm = shmget(key_shm, sizeof(struct Coda), 0) /*TODO*/;
	if (ds_shm == -1)
		die("shmget");

	coda = (struct Coda *)shmat(ds_shm, NULL, 0) /*TODO*/;
	if (coda == (void *)-1)
		die("shmat");

	// ottenimento array semafori

	key_t key_sem;
	key_sem = ftok(".", 'b') /*TODO*/;
	if (key_sem == -1)
		die("ftok");

	ds_sem = semget(key_sem, 4, 0) /*TODO*/;
	if (ds_sem == -1)
		die("semget");

	// TODO Creazione e Inizializzazione struttura locale
	Count *count = (Count *)malloc(sizeof(Count)) /*TODO*/;

	parametri param[NUM_WORKER];

	// Avvio dei thread
	for (i = 0; i < NUM_WORKER; i++)
	{
		printf("[SERVER] - creo thread %d...\n", i);
		// TODO creazione threads
		param[i].id = i;
		param[i].count = count;
		pthread_create(&threads[i], &attr, worker, (void *)&param[i]);
	}

	for (k = 0; k < NUM_WORKER; k++)
	{
		// TODO join
		pthread_join(threads[k], NULL);
	}

	// TODO rimozione struttura locale
	remove_buffer(count);
	printf("[SERVER] - bye bye...\n");
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
}
