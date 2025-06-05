#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"


int main(){
	//ottenimento e attach shared memory
	key_t key_shm;
	key_shm = /*TODO*/;

	int ds_shm = /*TODO*/;

	struct Coda * c;
	c = /*TODO*/;
	
	//ottenimento semafori

	key_t key_sem;
	key_sem = /*TODO*/;

	ds_sem = /*TODO*/;
    
	printf("[Client %d] - invio richieste...\n",getpid());

	int i = 0;
	int num_prenotazioni;	


	while(i < NUM_REQ){
		num_prenotazioni = ;//TODO numero casuale
		//TODO invio richiesta tramite funzione "produci"
	
		sleep(1);
		i++;
	}
	//TODO invio richiesta di terminazione (-1)

	printf("[Client %d] - Fine processo\n",getpid());

	return 0;
}
