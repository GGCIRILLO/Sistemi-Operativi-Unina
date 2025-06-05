#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "header_msg.h"

int main() {

    /* TBD: Creare le code di messaggi */

    int id_queue_collettore_1 = msgget(IPC_PRIVATE, IPC_CREAT|0664) /* TBD */;


    int id_queue_collettore_2 = msgget(IPC_PRIVATE, IPC_CREAT|0664) /* TBD */;


    int id_queue_server = msgget(IPC_PRIVATE, IPC_CREAT|0664) /* TBD */;


    /* TBD: Creare il processo figlio Server, 
            passandogli lo id della coda */
        pid_t pid = fork();
        if(pid==0){
                printf("[%d]Inizio Server\n",getpid());
                server(id_queue_server);
                exit(0);        
        }


    int id_collettore = 1;

    /* TBD: Creare il primo processo figlio Collettore, 
            passandogli lo "id_collettore",
            lo id della coda per ricevere dai sensori,
            e lo id della coda per inviare al server
    */
    pid = fork();
    if(pid==0){
        printf("[%d]Inizio Collettore 1\n",getpid());
        collettore(id_collettore, id_queue_collettore_1, id_queue_server);
        exit(0);
    }



    id_collettore = 2;
    
    /* TBD: Creare il secondo processo figlio Collettore, 
            passandogli lo "id_collettore",
            lo id della coda per ricevere dai sensori,
            e lo id della coda per inviare al server
    */
    pid = fork();
    if(pid==0){
        printf("[%d]Inizio Collettore 2\n",getpid());
        collettore(id_collettore, id_queue_collettore_2, id_queue_server);
        exit(0);
    }


    for(int i=0; i<NUM_SENSORI_PER_COLLETTORE; i++) {

        int id_sensore = i+1;

        /* TBD: Creare i processi figli Sensore, 
                passandogli lo "id_sensore",
                e lo id della coda per inviare al primo collettore
        */
        pid_t pid_s = fork();
        if(pid_s ==0){
                printf("[%d]Inizio Sensore %d per il collettore 1\n",getpid(),id_sensore);
                sensore(id_sensore, id_queue_collettore_1);
                exit(0);
        }

    }


    for(int i=0; i<NUM_SENSORI_PER_COLLETTORE; i++) {

        int id_sensore = i+1;

        /* TBD: Creare i processi figli Sensore, 
                passandogli lo "id_sensore",
                e lo id della coda per inviare al secondo collettore
        */
        pid_t pid_s = fork();
        if(pid_s ==0){
                printf("[%d]Inizio Sensore %d per il collettore 2\n",getpid(),id_sensore);
                sensore(id_sensore, id_queue_collettore_2);
                exit(0);
        }
    }



    /* TBD: Attendere la terminazione di tutti i processi figli */
    while(wait(NULL)>0);

    /* TBD: De-allocare le code di messaggi */
    msgctl(id_queue_collettore_1, IPC_RMID, NULL);
    msgctl(id_queue_collettore_2, IPC_RMID, NULL);
    msgctl(id_queue_server, IPC_RMID, NULL);

    
    return 0;
}