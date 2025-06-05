#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "header.h"


int main(int argc, char *argv[]){
	int coda;
	pid_t pid;
	long id_sensore;
        
	if (argc < 2 ) {
		printf("ERRORE: il client deve ricevere il proprio ID\n");
		return -1;
	}
        
	id_sensore = atol(argv[1]);
       
	key_t key;
	key = ftok(".", 'q'); //TODO:inserire la chiave
    
	coda = msgget(key, IPC_CREAT|0664); //TODO:inizializzare la coda

	printf("[DEBUG] - sensore id coda %d\n",coda);	
	printf("[Client %d] - invio richieste...\n",getpid());


	int i = 0;
	Misura misura;	

	srand(time(NULL));
	
	// TODO: inviare in cilco NUM_REQ misure da inviare al server tramite coda
	for (int i=0;i<NUM_REQ;i++){
		misura.id_client = id_sensore;
		misura.valore = rand() % 101;
		if(msgsnd(coda, (void*)&misura, sizeof(misura)-sizeof(long), 0)<0) die("msgsnd");
	}


	printf("[Client %d] - Fine processo\n",getpid());

	return 0;
}
