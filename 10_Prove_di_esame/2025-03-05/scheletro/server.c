#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "header_msg.h"
#include "header_prodcons.h"

struct parametri_thread_1 {

    /* TBD: Inserire in questa struttura dati i parametri per il thread 1,
            includendo il buffer b1, e gli identificativi delle code di messaggi
    */
};

struct parametri_thread_2 {
    /* TBD: Inserire in questa struttura dati i parametri per il thread 1,
            includendo il buffer b1 e il buffer b2
    */
};

struct parametri_thread_3 {
    /* TBD: Inserire in questa struttura dati i parametri per il thread 1,
            includendo il buffer b2
    */
};

void * thread_1(void *);
void * thread_2(void *);
void * thread_3(void *);

int main() {

    /* TBD: Ottenere gli identificativi delle code di messaggi */

    struct buffer * b1 = /* TBD: Inizializzare il puntatore alla struttura dati */
    struct buffer * b2 = /* TBD: Inizializzare il puntatore alla struttura dati */

    buffer_init(b1);
    buffer_init(b2);


    struct parametri_thread_1 * p1 = /* TBD: Inizializzare il puntatore alla struttura dati */

    /* TBD: Inizializzare i valori nella struttura "p1" */

    struct parametri_thread_2 * p2 = /* TBD: Inizializzare il puntatore alla struttura dati */

    /* TBD: Inizializzare i valori nella struttura "p2" */


    struct parametri_thread_3 * p3 = /* TBD: Inizializzare il puntatore alla struttura dati */

    /* TBD: Inizializzare i valori nella struttura "p3" */


    /* TBD: Creare i 3 thread, passandogli le 3 strutture dati con i parametri */


    /* TBD: Attendere la terminazione dei 3 thread */

}


void * thread_1(void * x) {

    /* TBD: Completare il passaggio dei parametri */

    struct rts rts;
    struct ots ots;
    struct richiesta r;


    for(int i=0; i<3; i++) {

        /* TBD: Ricevere il messaggio "request to send" */

        printf("[THREAD 1] Ricevuto messaggio RTS\n");



        /* TBD: Inviare il messaggio "ok to send" */

        printf("[THREAD 1] Inviato messaggio OTS\n");



        /* TBD: Ricevere il messaggio con il valore */


        int valore = /* TBD */;

        printf("[THREAD 1] Ricevuto messaggio MSG con valore %d\n", valore);


        buffer_produci(/* TBD */, valore);

        printf("[THREAD 1] Inserito valore %d nel buffer 1\n", valore);
    }

    pthread_exit(NULL);
    
}

void * thread_2(void * x) {

    /* TBD: Completare il passaggio dei parametri */

    int valore;

    for(int i=0; i<3; i++) {

        valore = buffer_consuma(/* TBD */);


        printf("[THREAD 2] Prelevato valore %d dal buffer 1\n", valore);


        sleep(2);


        valore = valore * 2;

        buffer_produci(/* TBD */, valore);

        printf("[THREAD 2] Inserito valore %d nel buffer 2\n", valore);
    }

    pthread_exit(NULL);
}

void * thread_3(void * x) {

    /* TBD: Completare il passaggio dei parametri */

    int valore;

    for(int i=0; i<3; i++) {

        valore = buffer_consuma(/* TBD */);

        printf("[THREAD 3] Prelevato valore %d dal buffer 2\n", valore);

        sleep(1);

        valore = valore + 1;

        printf("[THREAD 3] Valore finale: %d\n", valore);

    }

    pthread_exit(NULL);
}

