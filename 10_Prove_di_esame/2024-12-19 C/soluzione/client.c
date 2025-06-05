#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

void bambino(int queue_req, int queue_res) {
	int i;
	for (i=0; i < NUM_LETTERE; i++) {
		/*
        	TODO: invio del messaggio
    	*/
		MessaggioRichiesta msg;
		msg.tipo = MESSAGGIO;
    	
		/* TODO */ msg.numero_regali = rand() % 3 + 1;
		int ret = msgsnd(queue_req, (void*)&msg, sizeof(MessaggioRichiesta)-sizeof(long), 0);
		if (ret<0) die("msgsnd");

		printf("Invio lettera a Babbo Natale chiedendo %d regali\n", msg.numero_regali);

		/*
        	TODO: attesa del messaggio di risposta
    	*/

		MessaggioRisposta m;
		ret = msgrcv(queue_res, (void*)&m, sizeof(MessaggioRisposta)-sizeof(long), 0, 0);

		printf("Ho ricevuto la conferma di ricezione!\n");
		sleep(1);
	}
}

int main() {
	int pid;
	/*
        TODO: recupero code di messaggi
    */
	key_t k_req = ftok(".", 'a');
    if (k_req<0) die("ftok");

    key_t k_res = ftok(".", 'b');
    if (k_res<0) die("ftok");

    int coda_richieste = msgget(k_req, 0);

    int coda_risposte = msgget(k_res, 0);

    if (coda_richieste == -1 || coda_risposte == -1) die("msgget");

	int i;
	for (int i = 0; i < NUM_BAMBINI; i++) {
		/*
        	TODO: completare creazione figli 
    	*/	
		pid_t pid = fork();
		if (pid<0) die("fork");
		else if (pid==0){ 	
            srand(time(NULL)*getpid());
			printf("Bambino %d sta scrivendo la letterina...\n",getpid());
			bambino(coda_richieste, coda_risposte);
			exit(0);
		}
	}

	/*
        TODO: attesa terminazione figli
    */
	while(wait(NULL)>0);

	msgctl(coda_richieste,IPC_RMID,0);
	msgctl(coda_risposte,IPC_RMID,0);

	return 0;
}
