#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "header_msg.h"

void sensore(int id_sensore, int id_queue_collettore) {

    srand(getpid());

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        messaggio_sensore m;

        int valore = (rand() % 10) + 10;

        /* TBD: Inviare "valore" mediante messaggio */

        printf("[SENSORE] Inviato valore=%d\n", valore);


        sleep(3);
    }
}