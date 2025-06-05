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
	key_t chiave_shm = IPC_PRIVATE; // TODO
	key_t chiave_mbx = IPC_PRIVATE; // TODO
	if (chiave_mbx<0 || chiave_shm<0) die("key");

	id_shm = shmget(chiave_shm, sizeof(MonitorRisultati), IPC_CREAT|0664); //TODO
	id_queue = msgget(chiave_mbx, IPC_CREAT|0664); // TODO
	if (id_queue<0 || id_shm<0) die("shm msg get");


	MonitorRisultati * ls = (MonitorRisultati*) shmat(id_shm, NULL, 0); // TODO
	if(ls==(void*)-1){
		perror("Errore SHMAT");
		exit(1);
	}

	// TODO: inizializzare struttura
	ls->testa=0;
	ls->coda=0;
	ls->count=0;
	init_monitor(&ls->m, 2);
	
	pid_t pid;

	int j;
	for(j=0; j < N_STAMPA ; j++) {
		
		// TODO
		pid=fork();
		if (pid<0) die("fork");
		else if (pid==0){
			printf("[%d]Inizio Stampa\n",getpid());
			stampa(ls);	
			exit(0);
		}
	}

	
	for(j=0; j < N_FILTRI ; j++) {
		// TODO
		pid=fork();
		if (pid<0) die("fork");
		else if (pid==0){
			printf("[%d]Inizio Filtro\n",getpid());
			filtro(ls, id_queue);
			exit(0);
		}
	}

	for(j=0; j < N_GENERATORI ; j++) {
	
		// TODO
		pid=fork();
		if (pid<0) die("fork");
		else if (pid==0){
			printf("[%d]Inizio Generazione\n",getpid());
			generazione(id_queue);
			exit(0);	
		}
	}

	// TODO: attendere terminazione processi figli
	while(wait(NULL)>0);
	
	// TODO: deallocazione strutture
	remove_monitor(&ls->m);
	shmctl(id_shm, IPC_RMID, NULL);
	msgctl(id_queue, 0, IPC_RMID);

	return 0;
	
}





