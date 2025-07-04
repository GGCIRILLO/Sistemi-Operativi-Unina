#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

static void die(const char *msg){
	perror(msg);
	exit(1);
}

int main(){

	/* TBD: Creare una variabile M di tipo "Monitor", e inizializzarla con init_monitor() */
	Monitor M;
	init_monitor(&M, NUM_CONDITIONS);

	key_t id_meteo = shmget(IPC_PRIVATE,sizeof(Buffer),IPC_CREAT|0664);
	Buffer * buf = (Buffer*) (shmat(id_meteo,0,0));

	/* TBD: inizializzare la struttura Buffer */
	if(buf==(void*)-1) die("Errore shmat");
	buf->num_lettori=0;
	buf->num_scrittori=0;
	buf->meteo.temperatura=0;
	buf->meteo.umidita=0;
	buf->meteo.pioggia=0;
	

	pid_t pid;

	int k;
	for (k=0; k<NUM_UTENTI; k++) {

		pid=fork();
		if (pid==0) {
			Utente(&M,buf);
			exit(0);
     	} else if(pid<0) {
			perror("fork");
		}
	}


	pid=fork();
	if (pid==0) {
		Servizio(&M,buf);
		exit(0);
	} else if(pid<0) {
		perror("fork");
	}


	int status;
	for (k=0; k<NUM_UTENTI+1; k++) {
		pid=wait(&status);
		if (pid==-1)
			perror("errore");
	}

	/* TBD: Deallocare la variabile Monitor con remove_monitor() */
	remove_monitor(&M);

	shmctl(id_meteo,IPC_RMID,0);

	return 0;
}