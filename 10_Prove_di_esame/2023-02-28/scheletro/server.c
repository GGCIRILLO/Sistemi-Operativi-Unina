#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#include "header_prodcons.h"
#include "header_msg.h"

void server(int id_queue_server) {

    BufferProdCons * b = /* TBD: Creare e inizializzare l'oggetto monitor */


    /* TBD: Creare un thread, 
            e fargli eseguire la funzione "visualizza()",
            passandogli in ingresso l'oggetto monitor
     */


    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        int somma_valori = 0;
        int media = 0;

        for(int j=0; j<NUM_COLLETTORI; j++) {

            int id_collettore = j+1;

            messaggio_collettore m;

            /* TBD: Ricevere un messaggio da un collettore, con ricezione selettiva */

            int valore = /* TBD */;

            printf("[SERVER] Ricevuto valore=%d\n", valore);

            somma_valori += valore;

        }

        media = somma_valori / NUM_COLLETTORI;

        /* TBD: Chiamare la funzione "produci_valore()",
                passandogli la variabile "media"
        */

    }


    /* TBD: Attendere la terminazione del thread, de-allocare il monitor */

}

void * visualizza(void * p) {

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        int valore = /* TBD: Utilizzare la funzione "consuma_valore()" */

        printf("[VISUALIZZA] Valore=%d\n", valore);
    }

    return NULL;
}


void produci_valore(BufferProdCons * b, int valore) {

    /* TBD: Completare questa funzione introducendo la sincronizzazione */

    b->valore = valore;
    b->stato = PIENO;

}

int consuma_valore(BufferProdCons * b) {

    /* TBD: Completare questa funzione introducendo la sincronizzazione */

    int valore = b->valore;

    b->stato = VUOTO;

    return valore;
}
