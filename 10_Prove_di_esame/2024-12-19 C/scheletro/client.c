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
    	
		/* TODO */ = rand() % 5 + 1;
		printf("Invio lettera a Babbo Natale chiedendo %d regali\n", msg.numero_regali);


		/*
        	TODO: attesa del messaggio di risposta
    	*/
		printf("Ho ricevuto la conferma di ricezione!\n");
		sleep(1);
	}
}

int main() {
	int pid;
	/*
        TODO: recupero code di messaggi
    */

	int i;
	for (int i = 0; i < NUM_BAMBINI; i++) {
		/*
        	TODO: completare creazione figli 
    	*/		
            srand(time(NULL)*getpid());
			printf("Bambino %d sta scrivendo la letterina...\n",getpid());
			
		
	}

	/*
        TODO: attesa terminazione figli
    */

	msgctl(queue_req,IPC_RMID,0);
	msgctl(queue_res,IPC_RMID,0);

	return 0;
}
