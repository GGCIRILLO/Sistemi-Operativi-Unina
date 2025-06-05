#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "pubsub.h"

void subscriber(int id_coda_registrazioni, long topic);

int main() {

    srand(getpid());



    
    key_t chiave_coda_registrazioni = ftok(".", 'r'); /* TBD */
    if (chiave_coda_registrazioni<0) die("ftok");

    int id_coda_registrazioni = msgget(chiave_coda_registrazioni, IPC_CREAT|0664); /* TBD: Creare una coda di messaggi di registrazione */
    if (id_coda_registrazioni<0) die("msgget");




    for(int i=0; i<NUM_SUBSCRIBERS_PER_TOPIC; i++) {

        printf("[SUBSCRIBER] Avvio processo subscriber su topic 1\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "subscriber".
            Passare come parametri lo ID della coda per le registrazioni, e il valore TOPIC1.
        */
        pid_t pid = fork();
        if (pid<0) die("fork");
        else if (pid==0) {
            subscriber(id_coda_registrazioni, TOPIC1);
            exit(0);
        }
    }


    for(int i=0; i<NUM_SUBSCRIBERS_PER_TOPIC; i++) {

        printf("[SUBSCRIBER] Avvio processo subscriber su topic 2\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "subscriber".
            Passare come parametri lo ID della coda per le registrazioni, e il valore TOPIC2.
        */
        pid_t pid = fork();
        if (pid<0) die("fork");
        else if (pid==0) {
            subscriber(id_coda_registrazioni, TOPIC2);
            exit(0);
        }
    }


    printf("[SUBSCRIBER] Attesa terminazione processi figli\n");

    /* TBD: Attendere la terminazione dei processi figli */
    while(wait(NULL)>0);

}

void subscriber(int id_coda_registrazioni, long topic) {


    key_t chiave_coda_messaggi_subscriber = IPC_PRIVATE; /* TBD */

    int id_coda_messaggi_subscriber = msgget(chiave_coda_messaggi_subscriber, IPC_CREAT|0664); /* TBD: Creare una coda di messaggi privata del subscriber */
    if (id_coda_messaggi_subscriber<0) die("msgget");

    messaggio_registrazione registrazione;

    /* TBD: 
        Inviare un messaggio di registrazione al broker.
        Includere nel messaggio lo ID della coda di messaggi privata.
    */
    registrazione.topic = topic;
    registrazione.id_coda = id_coda_messaggi_subscriber;
    if (msgsnd(id_coda_registrazioni, (void*)&registrazione, sizeof(registrazione)-sizeof(long), 0)<0) die("msgsnd");

    printf("[SUBSCRIBER] invio richiesta registrazione topic: %ld\n", topic);

    for(int i=0; i<NUM_MESSAGGI*NUM_PUBLISHERS_PER_TOPIC; i++) {

        messaggio_valore messaggio;

        /* TBD: Ricevere un messaggio dal broker */
        int ret = msgrcv(id_coda_messaggi_subscriber, (void*)&messaggio, sizeof(messaggio)-sizeof(long), topic, 0);
        if (ret<0) die("msgrcv");

        int valore = messaggio.valore /* TBD */;

        printf("[SUBSCRIBER] Ricevuto messaggio: topic=%ld, valore=%d\n", topic, valore);

    }

    /* TBD: Deallocare la coda di messaggi privata del subscriber */
    msgctl(id_coda_messaggi_subscriber, IPC_RMID, NULL);

}

