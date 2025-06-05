#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "header_msg.h"
#include "header_sem.h"


void server(/* TBD: Completare il passaggio di parametri */ prodcons*,prodcons*, int, int, int);


int main() {


    /* TBD: Ottenere gli identificativi delle code di messaggi */
	key_t key_send = ftok(".", 'S');
    key_t key_rcv = ftok(".", 'R');
    
    int send_queue=msgget(key_send, IPC_CREAT| 0664);
    int rcv_queue=msgget(key_rcv, IPC_CREAT | 0664);
	
	


    for(int richieste=0; richieste<2; richieste++) {

        msg_init_request req;
        msg_init_response res;


        /* TBD: ricevere un messaggio dal client */
		int ret = msgrcv(send_queue, &req, sizeof(req)-sizeof(long), 0, 0);
		if (ret<0){
			perror("errore ricezione richiesta");
			exit(1);
		}
       

        int num_valori = req.valori_richiesti/* TBD */;
        int pid_client = req.pid /* TBD */;

        printf("[SERVER %d] Ricezione richiesta (num. valori: %d)\n", getpid(), num_valori);


        /* TBD: Allocare e inizializzare le risorse che saranno condivise
                tra il client e il processo server figlio
         */
		
		int id_sem_invio =semget(IPC_PRIVATE, 4, IPC_CREAT | 0664)/* TBD */;        
		int id_shm_invio = shmget(IPC_PRIVATE, sizeof(prodcons), IPC_CREAT | 0664)/* TBD */;
 
        int id_sem_ricezione = semget(IPC_PRIVATE, 4, IPC_CREAT | 0664)/* TBD */;
        int id_shm_ricezione = shmget(IPC_PRIVATE, sizeof(prodcons), IPC_CREAT | 0664)/* TBD */;

		int sem1 = id_sem_invio;
		int sem2 = id_sem_ricezione;

		if(id_shm_invio<0){
			perror("Errore nel descrittore shared memory lato server\n");
			exit(1);
		
		}
		if(id_shm_ricezione<0){
			perror("Errore nel descrittore shared memory lato server\n");
			exit(1);
		
		}
		if(id_sem_invio<0){
			perror("Errore nel descrittore semaforo 1 lato server\n");
			exit(1);
		
		}
		
		if(id_sem_ricezione<0){
			perror("Errore nel descrittore semaforo 2 lato server\n");
			exit(1);
		
		}
		
		semctl(sem1, SPAZIO_DISPONIBILE, SETVAL, DIM);
		semctl(sem1, MESSAGGIO_DISPONIBILE, SETVAL, 0);
		semctl(sem1, MUTEXP, SETVAL, 1);
		semctl(sem1, MUTEXC, SETVAL, 1);
		
		semctl(sem2, SPAZIO_DISPONIBILE, SETVAL, DIM);
		semctl(sem2, MESSAGGIO_DISPONIBILE, SETVAL, 0);
		semctl(sem2, MUTEXP, SETVAL, 1);
		semctl(sem2, MUTEXC, SETVAL, 1);

        /* TBD: Inviare il messaggio di risposta al client, 
                con gli identificativi delle risorse condivise
         */
		res.type = MSG_TYPE;
		res.id_shm_send = id_shm_invio;
    	res.id_shm_rcv = id_shm_ricezione;
		res.id_sem_send = sem1;
		res.id_sem_rcv = sem2;

        

        printf("[SERVER %d] Inviato risposta\n", getpid());

    	ret=msgsnd(rcv_queue, &res, sizeof(res)-sizeof(long), 0);
    	if(ret<0){
    		perror("Errore nella send lato server\n");
    		exit(1);
    	}
    	
    	prodcons* p1;
    	prodcons* p2;
    	
    	p1=(prodcons*)shmat(id_shm_invio, NULL, 0);
    	p2=(prodcons*)shmat(id_shm_ricezione, NULL, 0);
    	p1->testa=0;
    	p1->coda=0;
    	p2->testa=0;
    	p2->coda=0;

        /* TBD: Creare un processo server figlio, e
                passargli i riferimenti alle risorse condivise
         */
		pid_t pid = fork();
		if (pid<0){
			perror("Errore fork");
			exit(1);
		} else if (pid==0){
			printf("Creazione processo figlio nel server\n");
			server(p1, p2, num_valori, sem1, sem2);
			exit(0);
		}

		shmdt(p1);
        shmdt(p2);
    }

	while (wait(NULL)>0);

	return 0;
}



void server(prodcons* p1,prodcons* p2, int val, int id_sem1, int id_sem2) {

    int num_valori = val/* TBD */;

    for(int i=0; i<num_valori; i++) {


        int ricevuto = consuma(id_sem1,p1);

        printf("[SERVER %d] Valore ricevuto: %d\n", getpid(), ricevuto);
		fflush(stdout);

        int valore = ricevuto * 2;

        produci(id_sem2, p2, valore);
        printf("[SERVER %d] Valore inviato: %d\n", getpid(), valore);
		fflush(stdout);

    }

    
    semctl(id_sem1, 0, IPC_RMID);
    semctl(id_sem2, 0, IPC_RMID);

}
