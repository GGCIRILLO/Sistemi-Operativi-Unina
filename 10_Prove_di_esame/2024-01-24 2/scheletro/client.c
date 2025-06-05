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




    for(int i=0; i<NUM_RICHIESTE; i++) {

        int buffer = rand() % NUM_BUFFER;

        int value = rand() % 10;


        /* TBD: Inviare un messaggio contenente "value" e "buffer".

                È richiesto che l'invio sia effettuato
                tramite send sincrona.
         */


        sleep(2);

    }




}