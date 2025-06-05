#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "header_msg.h"

void sensore(int id_sensore, int id_queue_collettore) {

    srand(getpid());

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {


        int valore = (rand() % 10) + 10;

        //TODO: invio del valore al collettore
        messaggio_sensore m;
        m.sensore = id_sensore;
        m.valore = valore;

        int ret = msgsnd(id_queue_collettore, (void*)&m, sizeof(m)-sizeof(long), 0);
        if (ret<0) die("msgnsd");

        printf("[SENSORE %d] Inviato valore=%d\n", id_sensore, valore);

        sleep(1);
    }
}