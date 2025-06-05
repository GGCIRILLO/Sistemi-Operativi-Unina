#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "header.h"


void reader(int queue_req, int queue_res) {
	int i;
	for (i=0; i < NUM_READS; i++) {
		req msg;
		//TODO: preparazione messaggio di richiesta
		msg.type=MESSAGGIO;
		msg.pid=getpid();
		
		printf("READER %d: invio richiesta \n",getpid());
		//TODO: invio richiesta
		msgsnd(queue_req, (void*)&msg, sizeof(req)-sizeof(long), 0);
		//TODO: ricezione risposta
		res risp;
		msgrcv(queue_res, (void*)&risp, sizeof(res)-sizeof(long), getpid(), 0);
		
		printf("READER %d: letto valore: %d\n",getpid(),risp.value);
		sleep(1);
	}
}

int main() {

	int pid;
    key_t msg_req_key = ftok(".",'a'); //TODO: definire chiave
	key_t msg_res_key = ftok(".",'b'); //TODO: definire chiave

    //TODO: INIZIALIZZAZIONE CODE
	int queue_res = msgget(msg_res_key,0);
    int queue_req = msgget(msg_req_key,0);
	
	int i;
	for (int i = 0; i < NUM_READERS; i++) {
		pid = fork();
		if (pid==0){
			printf("READER %d avviato\n",getpid());
			reader(queue_req,queue_res);
			_exit(0);
		}
	}

	for (int i = 0; i < NUM_READERS; i++) 
		wait(NULL);

	//TODO: rimozione code
	msgctl(queue_res,IPC_RMID, NULL);
    msgctl(queue_req,IPC_RMID, NULL);

	return 0;
}
