#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "header.h"

#define NUM_CLIENT 3
#define NUM_SERVER 1

int main(){
	//ottenimento e attach shared memory
	key_t key_shm;
	key_shm = /*TODO*/;

	int ds_shm = /*TODO*/;

	struct Coda * c;
	c = /*TODO*/;
	
	//ottenimento array semafori

	key_t key_sem;
	key_sem = /*TODO*/;

	ds_sem = /*TODO*/;
	
	//TODO inizializzazione coda e semafori

  
	int i = 0;
	int pid;
	int status;
	
	for( i = 0; i < NUM_CLIENT+NUM_SERVER; i++){
		
		sleep(1);

		pid = fork();

		if(pid == 0){

			if(i == NUM_CLIENT+NUM_SERVER -1){
				//TODO aggiungere exec per avviare il server
			}else{
				//TODO aggiungere exec per avviare il client
				exit(-1);
			}
		}
	}

	for(i = 0; i < NUM_CLIENT+NUM_SERVER;i++){

		wait(&status);

		if (WIFEXITED(status)) {
    			printf("[PADRE] - Figlio terminato con stato %d\n",status);
  		}
	}

	//TODO rimozione array semafori e memoria condivisa

	printf("[PADRE] - Fine elaborazione...\n");

	return 0;	
}
