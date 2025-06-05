#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "pubsub.h"

void subscriber(int id_coda_registrazioni, long topic);

int main() {

    srand(getpid());



    
    key_t chiave_coda_registrazioni = /* TBD */

    int id_coda_registrazioni = /* TBD: Creare una coda di messaggi di registrazione */





    for(int i=0; i<NUM_SUBSCRIBERS_PER_TOPIC; i++) {

        printf("[SUBSCRIBER] Avvio processo subscriber su topic 1\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "subscriber".
            Passare come parametri lo ID della coda per le registrazioni, e il valore TOPIC1.
        */
    }


    for(int i=0; i<NUM_SUBSCRIBERS_PER_TOPIC; i++) {

        printf("[SUBSCRIBER] Avvio processo subscriber su topic 2\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "subscriber".
            Passare come parametri lo ID della coda per le registrazioni, e il valore TOPIC2.
        */
    }


    printf("[SUBSCRIBER] Attesa terminazione processi figli\n");

    /* TBD: Attendere la terminazione dei processi figli */

}

void subscriber(int id_coda_registrazioni, long topic) {


    key_t chiave_coda_messaggi_subscriber = /* TBD */

    int id_coda_messaggi_subscriber = /* TBD: Creare una coda di messaggi privata del subscriber */


    messaggio_registrazione registrazione;

    /* TBD: 
        Inviare un messaggio di registrazione al broker.
        Includere nel messaggio lo ID della coda di messaggi privata.
    */

    for(int i=0; i<NUM_MESSAGGI*NUM_PUBLISHERS_PER_TOPIC; i++) {

        messaggio_valore messaggio;

        /* TBD: Ricevere un messaggio dal broker */

        int valore = /* TBD */;

        printf("[SUBSCRIBER] Ricevuto messaggio: topic=%ld, valore=%d\n", topic, valore);

    }

    /* TBD: Deallocare la coda di messaggi privata del subscriber */

}

