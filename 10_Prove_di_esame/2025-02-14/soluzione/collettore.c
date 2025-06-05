#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "header_msg.h"


void collettore(int id_queue_collettore, int id_queue_server) {

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        int somma_valori = 0;
        int media = 0;

        int ret;

        for(int j=0; j<NUM_SENSORI; j++) {

            //TODO: riceve un messaggio da ogni sensore
            messaggio_sensore m;

            ret = msgrcv(id_queue_collettore, (void*)&m, sizeof(messaggio_sensore)-sizeof(long), j+1, 0);
            if (ret<0) die("msgrcv");

            int valore = m.valore ;//TODO;

            printf("[COLLETTORE] Ricevuto valore=%d\n", valore);

            somma_valori += valore;
        }


        media = somma_valori/NUM_SENSORI ;//TODO: calcolo media

        //TODO manda la media al server
        messaggio_collettore mc;
        mc.media = media;
        mc.tipo = TIPO_MESSAGGIO;
        ret = msgsnd(id_queue_server, (void*)&mc, sizeof(messaggio_collettore)-sizeof(long), 0);
        if (ret<0) die("msgsnd");
        
        printf("[COLLETTORE] Inviato valore=%d\n", media);

    }
}
