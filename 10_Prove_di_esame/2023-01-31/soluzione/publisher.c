#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "pubsub.h"

void publisher(int id_coda_messaggi, long topic);

int main() {


    key_t chiave_coda_messaggi = ftok(".", 'p'); /* TBD */
    if (chiave_coda_messaggi<0) die("ftok");

    int id_coda_messaggi = msgget(chiave_coda_messaggi, IPC_CREAT|0664); /* TBD: Creare una coda di messaggi dei publisher */
    if (id_coda_messaggi<0) die("msgget");

    for(int i=0; i<NUM_PUBLISHERS_PER_TOPIC; i++) {

        printf("[PUBLISHER] Avvio processo publisher su topic 1\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "publisher".
            Passare come parametri lo ID della coda messaggi, e il valore TOPIC1.
        */
        pid_t pid = fork();
        if (pid<0) die("fork");
        else if (pid==0) {
            publisher(id_coda_messaggi, TOPIC1);
            exit(0);
        }

    }


    for(int i=0; i<NUM_PUBLISHERS_PER_TOPIC; i++) {

        printf("[PUBLISHER] Avvio processo publisher su topic 2\n");

        /* TBD: 
            Creare un processo figlio, che esegua la funzione "publisher".
            Passare come parametri lo ID della coda messaggi, e il valore TOPIC2.
        */
                pid_t pid = fork();
        if (pid<0) die("fork");
        else if (pid==0) {
            publisher(id_coda_messaggi, TOPIC2);
            exit(0);
        }
    }


    printf("[PUBLISHER] Attesa terminazione processi figli\n");

    /* TBD: Attendere la terminazione dei processi figli */
    while(wait(NULL)>0);

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
        messaggio.topic = topic;
        messaggio.valore = valore;

        if (msgsnd(id_coda_messaggi, (void*)&messaggio, sizeof(messaggio_valore)-sizeof(long), 0)<0) die("msgsnd");

        printf("[PUBLISHER] Messaggio inviato: topic=%ld, valore=%d\n", topic, valore);

        sleep(1);
    }
}

