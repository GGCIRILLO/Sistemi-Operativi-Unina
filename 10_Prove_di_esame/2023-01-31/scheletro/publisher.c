#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "pubsub.h"

void publisher(int id_coda_messaggi, long topic);

int main() {


    key_t chiave_coda_messaggi = /* TBD */

    int id_coda_messaggi = /* TBD: Creare una coda di messaggi dei publisher */






    for(int i=0; i<NUM_PUBLISHERS_PER_TOPIC; i++) {

        printf("[PUBLISHER] Avvio processo publisher su topic 1\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "publisher".
            Passare come parametri lo ID della coda messaggi, e il valore TOPIC1.
        */

    }


    for(int i=0; i<NUM_PUBLISHERS_PER_TOPIC; i++) {

        printf("[PUBLISHER] Avvio processo publisher su topic 2\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "publisher".
            Passare come parametri lo ID della coda messaggi, e il valore TOPIC2.
        */
    }


    printf("[PUBLISHER] Attesa terminazione processi figli\n");

    /* TBD: Attendere la terminazione dei processi figli */

}

void publisher(int id_coda_messaggi, long topic) {

    srand(getpid());

    for(int i=0; i<NUM_MESSAGGI; i++) {

        int valore = rand() % 100;

        messaggio_valore messaggio;

        /* TBD:
            Inviare un messaggio al processo broker.
            Includere il topic ed il valore.
        */

        printf("[PUBLISHER] Messaggio inviato: topic=%ld, valore=%d\n", topic, valore);

        sleep(1);
    }
}

