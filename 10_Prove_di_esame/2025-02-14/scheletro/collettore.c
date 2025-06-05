#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "header_msg.h"


void collettore(int id_queue_collettore, int id_queue_server) {

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        int somma_valori = 0;
        int media = 0;

        for(int j=0; j<NUM_SENSORI; j++) {

            //TODO: riceve un messaggio da ogni sensore

            int valore = ;//TODO;

            printf("[COLLETTORE] Ricevuto valore=%d\n", valore);

            somma_valori += valore;
        }


        media = ;//TODO: calcolo media

        //TODO manda la media al server

        

        printf("[COLLETTORE] Inviato valore=%d\n", media);


    }
}
