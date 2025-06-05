#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "header_msg.h"


void collettore(int id_collettore, int id_queue_collettore, int id_queue_server) {

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        int somma_valori = 0;
        int media = 0;

        for(int j=0; j<NUM_SENSORI_PER_COLLETTORE; j++) {

            int id_sensore = j+1;

            messaggio_sensore m;

            /* TBD: Ricevere un messaggio da un sensore, con ricezione selettiva */
            msgrcv(id_queue_collettore, (void*)&m, sizeof(messaggio_sensore)-sizeof(long), id_sensore, 0);

            int valore = m.valore /* TBD */;

            printf("[COLLETTORE] Ricevuto valore=%d\n", valore);

            somma_valori += valore;
        }


        media = somma_valori / NUM_SENSORI_PER_COLLETTORE;

        messaggio_collettore m;

        /* TBD: Inviare "media" al processo server */
        m.tipo= id_collettore;
        m.valore= (int) media;

        msgsnd(id_queue_server, (void*)&m, sizeof(messaggio_collettore)-sizeof(long), 0);

        printf("[COLLETTORE] Inviato valore=%d\n", media);


    }
}
