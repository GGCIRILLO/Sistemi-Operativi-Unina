#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

#include "header.h"


int main(){
	pid_t pid_ex,pid;
	int st,i;
	int shmid,semid;
	BufferMutuaEx* buf;

	key_t key_shm,key_sem;
	key_shm = // TODO 
	key_sem = // TODO 

	shmid = // TODO 
	semid = // TODO 
	
	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);

	// TODO: inizializzare semafori

	buf = // TODO 
	
	// TODO: inizializzazione della struttura
	
	srand(time(NULL));

	for(i = 0; i < NPROD; i++){
		pid = fork();
		
		// TODO: ogni figlio produttore (1 e 2) fa PRODS produzioni

	}

	for(i = 0; i < NCONS; i++){
		pid = fork();

		// TODO: ogni figlio consumatore (1 e 2) fa CONS consumi

	}
	
	// TODO: attesa completamento figli

	// TODO: rimozione strutture 

	return 0;
}

