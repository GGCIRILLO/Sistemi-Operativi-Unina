#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "header_msg.h"
#include "header_sem.h"


int main() {

    srand(getpid());


    /* TBD: Ottenere gli identificativi delle code di messaggi */

	
     if(send_queue<0){
    	perror("Errore nella creazione della coda sender lato client\n");
    	exit(1);
    }
	
	if(rcv_queue<0){
    	perror("Errore nella creazione della coda receiver lato client\n");
    	exit(1);
    }

    int num_valori = 10;

    msg_init_request req;
    msg_init_response res;
	

    printf("[CLIENT %d] Invio richiesta (num. valori: %d)\n", getpid(), num_valori);

    /* TBD: Inviare il messaggio di richiesta */
    
	

    /* TBD: Ricevere il messaggio di risposta */
    
    printf("[CLIENT %d] Ricevuto risposta\n", getpid());


    int id_shm_invio =/* TBD */;
    int id_sem_invio =/* TBD */;

    int id_shm_ricezione =/* TBD */;
    int id_sem_ricezione =/* TBD */;
    
	prodcons* p1;
	prodcons* p2;
	
	p1=(prodcons*) shmat(id_shm_invio, NULL, 0);
	p2=(prodcons*) shmat(id_shm_ricezione, NULL, 0);
    for(int i=0; i<num_valori; i++) {

        int valore = rand() % 10;


        produci(id_sem_invio, 	p1, valore);

        printf("[CLIENT %d] Valore inviato: %d\n", getpid(), valore);


        int ricevuto = consuma(id_sem_ricezione,p2 );

        printf("[CLIENT %d] Valore ricevuto: %d\n", getpid(), ricevuto);

    }




}
