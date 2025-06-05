#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int main()
{
	key_t key_shm;
	key_shm = ftok(".", 'a') /*TODO*/;
	if (key_shm == -1)
		die("ftok");

	int ds_shm = shmget(key_shm, sizeof(struct Coda), IPC_CREAT|0664) /*TODO*/;
	if (ds_shm == -1)
		die("shmget");

	struct Coda *c;
	c = (struct Coda *)shmat(ds_shm, NULL, 0) /*TODO*/;
	if (c == (void *)-1)
		die("shmat");

	// ottenimento array semafori

	key_t key_sem;
	key_sem = ftok(".", 'b') /*TODO*/;
	if (key_sem == -1)
		die("ftok");

	int ds_sem = semget(key_sem, 4, 0) /*TODO*/;
	if (ds_sem == -1)
		die("semget");

	printf("[Client %d] - invio richieste...\n", getpid());

	int i = 0;
	int num_prenotazioni;

	srand(time(NULL) + getpid());

	while (i < NUM_REQ)
	{
		num_prenotazioni = rand() % 5 + 1; // TODO numero casuale
		// TODO invio richiesta tramite funzione "produci"
		produci(c, ds_sem, num_prenotazioni);
		printf("[Client %d] - Richiesta %d inviata con %d num_prenotazioni\n", getpid(), i + 1, num_prenotazioni);

		sleep(1);
		i++;
	}
	// TODO invio richiesta di terminazione (-1)
	produci(c, ds_sem, -1);
	printf("[Client %d] - Richiesta di terminazione inviata\n", getpid());

	printf("[Client %d] - Fine processo\n", getpid());

	return 0;
}
