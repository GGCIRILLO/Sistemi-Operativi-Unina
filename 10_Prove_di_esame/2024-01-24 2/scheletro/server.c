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


void server(/* TBD: Completare il passaggio dei parametri */) {

    for(int i=0; i<10; i++) {

        sleep(1);

        int valore = leggi(/* TBD */);

        printf("[SERVER WORKER %d] Letto valore %d\n", getpid(), valore);

    }

}

int main() {


    /* TBD: Ottenere gli identificativi delle code di messaggi */



    int sem[NUM_BUFFER];
    int shm[NUM_BUFFER];
    lettscritt * ls[NUM_BUFFER];


    for(int i=0; i<NUM_BUFFER; i++) {

        /* TBD: Allocare il buffer su memoria condivisa */

        ls[i] = /* TBD */;
        shm[i] = /* TBD */;

        printf("[SERVER FRONTEND %d] Creato buffer %d (p=%p, id=%d)\n", getpid(), i, ls[i], shm[i]);


        sem[i] = /* TBD */;

        printf("[SERVER FRONTEND %d] Creato vettore semafori %d (id=%d)\n", getpid(), i, sem[i]);

    }


    for(int i=0; i<NUM_SERVER; i++) {

        /* TBD: 
            Creare un processo figlio (server worker),
            e fargli eseguire la funzione "server()".

            Passare al worker il riferimento
            a uno dei buffer e ai relativi semafori.

            Esempio: allo i-esimo processo server worker
            dovrà essere passato il semaforo "sem[i % NUM_BUFFER]".
        */

    }



    for(int i=0; i<NUM_RICHIESTE; i++) {


        /* TBD: Effettuare la ricezione del messaggio dal client (send sincrona) */

        int buffer = /* TBD */;
        int value = /* TBD */;

        printf("[SERVER FRONTEND %d] Ricevuto richiesta (valore=%d, buffer=%d)\n", getpid(), value, buffer);


        /* TBD: Completare il passaggio dei parametri.
                Passare alla funzione i riferimenti allo
                i-esimo buffer e ai relativi semafori.
         */

        scrivi(/* TBD */);
    }


    /* TBD: Attendere la terminazione dei processi figli e deallocare le risorse */



    return 0;
}