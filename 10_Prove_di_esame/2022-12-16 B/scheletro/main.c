#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>

#include "procedure.h"


int main() {

	int id_queue, id_shm;
	key_t chiave_shm = // TODO
	key_t chiave_mbx = // TODO

	id_shm = //TODO
	id_queue = // TODO


	MonitorRisultati * ls =// TODO
	if(ls==(void*)-1){
		perror("Errore SHMAT");
		exit(1);
	}

	// TODO: inizializzare struttura
	
	
	pid_t pid;

	int j;
	for(j=0; j < N_STAMPA ; j++) {
		
		// TODO
		
			printf("[%d]Inizio Stampa\n",getpid());
						
		}
	}

	
	for(j=0; j < N_FILTRI ; j++) {
		
		// TODO
			}

	for(j=0; j < N_GENERATORI ; j++) {
	
		// TODO
			}

	// TODO: attendere terminazione processi figli
	
	// TODO: deallocazione strutture
	
}





