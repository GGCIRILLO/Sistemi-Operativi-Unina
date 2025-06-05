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
	key_shm = IPC_PRIVATE; // TODO 
	key_sem = IPC_PRIVATE; // TODO 

	shmid = shmget(key_shm, sizeof(buf), IPC_CREAT|0664); // TODO 
	semid = semget(key_sem, 4, IPC_CREAT|0664); // TODO 
	if (shmid<0 || semid<0) die("shm/sem get");
	
	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);

	// TODO: inizializzare semafori
	semctl(semid, SPAZIO, SETVAL, DIM);
	semctl(semid, MESSAGGIO, SETVAL, 0);
	semctl(semid, MUTEXP, SETVAL, 1);
	semctl(semid, MUTEXC, SETVAL, 1);

	buf = (BufferMutuaEx *) shmat(shmid, NULL, 0); // TODO 
	if (buf==(void*)-1) die("shmat");
	
	// TODO: inizializzazione della struttura
	for (i=0; i<DIM;i++){
		buf->stato[i]=LIBERO;
	}
	
	srand(time(NULL));

	for(i = 0; i < NPROD; i++){
		pid = fork();
		if (pid<0) die("fork");

		// TODO: ogni figlio produttore (1 e 2) fa PRODS produzioni
		if (pid==0){
			srand(getpid()*time(NULL));
			int val = rand()%101;
			if (i%2==0){
				for (int j=0;j<PRODS;j++){
					produci_tipo_1(buf, semid, val);				
				}
			} else {
				for (int j=0;j<PRODS;j++){				
					produci_tipo_2(buf, semid, val);				
				}
			}
			exit(0);
		}
	}

	for(i = 0; i < NCONS; i++){
		pid = fork();
		if (pid<0) die("fork");

		// TODO: ogni figlio consumatore (1 e 2) fa CONS consumi
		if (pid==0){
			if (i%2==0){
				for (int j=0;j<CONS;j++){
					consuma_tipo_1(buf, semid);
				}
			} else {
				for (int j=0;j<CONS;j++){
					consuma_tipo_2(buf, semid);
				}
			}
			exit(0);
		}
	}
	
	// TODO: attesa completamento figli
	while(wait(NULL)>0);

	// TODO: rimozione strutture 
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);

	return 0;
}

