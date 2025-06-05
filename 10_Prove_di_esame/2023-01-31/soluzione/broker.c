#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <pthread.h>

#include "pubsub.h"

#define MAX_TOPICS 2
#define MAX_SUBSCRIBERS 2

int code[MAX_TOPICS][MAX_SUBSCRIBERS];

void * gestisci_registrazioni(void * arg);
void * gestisci_messaggi(void * arg);


int main() {

    // inizializzazione lista di code
    for(int i=0; i<MAX_TOPICS; i++) {
        for(int j=0; j<MAX_SUBSCRIBERS; j++) {
            code[i][j] = 0;
        }
    }


    key_t chiave_coda_registrazioni = ftok(".", 'r'); /* TBD */
    if (chiave_coda_registrazioni<0) die("ftok");

    int id_coda_registrazioni = msgget(chiave_coda_registrazioni, IPC_CREAT|0664); /* TBD: Creare una coda di messaggi di registrazione */
    if (id_coda_registrazioni<0) die("msgget");


    key_t chiave_coda_messaggi = ftok(".", 'p'); /* TBD */
    if (chiave_coda_messaggi<0) die("ftok");

    int id_coda_messaggi = msgget(chiave_coda_messaggi, IPC_CREAT|0664); /* TBD: Creare una coda di messaggi dei publisher */
    if (id_coda_messaggi<0) die("msgget");


    /* TBD:
        Creare un thread che esegua la funzione "gestisci_registrazioni".
        Passare come parametro alla funzione gli id delle code.
     */
    pthread_t thread_registrazioni;
    pthread_t thread_mess;

    pthread_create(&thread_registrazioni, NULL, gestisci_registrazioni, (void*)&id_coda_registrazioni); 

    /* TBD:
        Creare un thread che esegua la funzione "gestisci_messaggi".
        Passare come parametro alla funzione gli id delle code.
     */
    pthread_create(&thread_mess, NULL, gestisci_messaggi, (void*)&id_coda_messaggi);

    /* TBD: Attendere la terminazione dei 2 thread */
    pthread_join(thread_registrazioni,NULL);
    pthread_join(thread_mess,NULL);

    /* TBD: Deallocare le 2 code di messaggi */
    msgctl(id_coda_registrazioni, IPC_RMID, NULL);
    msgctl(id_coda_messaggi, IPC_RMID, NULL);

    pthread_exit(0);
}


void * gestisci_registrazioni(void * arg) {


    /* TBD: Completare il passaggio di parametri */
    int * coda_reg = (int*) arg;
    int ret;
    messaggio_registrazione m;

    for(int i=0; i<TOTALE_SUBSCRIBER; i++) {

        messaggio_registrazione messaggio;

        /* TBD: Ricevere un messaggio di registrazione */
        ret = msgrcv(*coda_reg, (void*)&m, sizeof(m)-sizeof(long), 0, 0);
        if (ret<0) die("msgrcv");

        long topic = m.topic /* TBD */;
        int id_coda = m.id_coda /* TBD */;

        printf("[BROKER] Ricevuto messaggio di registrazione: topic=%ld, id_coda=%d\n", topic, id_coda);


        // aggiungo il subscriber alla lista di code

        if(topic <= 0 || topic > MAX_TOPICS) {
            printf("[BROKER] Topic non valido\n");
            exit(1);
        }

        if(id_coda <= 0) {
            printf("[BROKER] Id coda non valido\n");
            exit(1);
        }

        int trovato = 0;
        for(int i=0; i<MAX_SUBSCRIBERS; i++) {
            if(code[topic-1][i] == 0) {
                code[topic-1][i] = id_coda;
                trovato = 1;
                break;
            }
        }

        if(trovato == 0) {
            printf("[BROKER] Numero massimo di subscriber raggiunto\n");
            exit(1);
        }

    }
    pthread_exit(0);
}


void * gestisci_messaggi(void * arg) {


    /* TBD: Completare il passaggio di parametri */
    int * coda_mess = (int *) arg;
    int ret;


    for(int i=0; i<TOTALE_MESSAGGI; i++) {

        messaggio_valore messaggio;

        /* TBD: Ricevere un messaggio dai publisher  */
        ret = msgrcv(*coda_mess, (void*)&messaggio, sizeof(messaggio_valore)-sizeof(long), 0, 0);
        if (ret<0) die("msgrcv");


        long topic = messaggio.topic/* TBD */;
        int valore = messaggio.valore/* TBD */;

        printf("[BROKER] Ricevuto messaggio: topic=%ld, valore=%d\n", topic, valore);



        // invio messaggio a tutti i subscriber registrati al topic

        if(topic <= 0 || topic > MAX_TOPICS) {
            printf("[BROKER] Topic non valido\n");
            exit(1);
        }

        for(int j=0; j<MAX_SUBSCRIBERS; j++) {

            int id_coda = code[topic-1][j];

            if(id_coda != 0) {

                /* TBD: Inviare il messaggio al subscriber in ascolto sulla coda "id_coda" */
                ret = msgsnd(id_coda, (void*)&messaggio, sizeof(messaggio)-sizeof(long), 0);
                if (ret<0) die("msgsnd");

            }
        }

    }
    pthread_exit(0);

    return NULL;
}
