#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#include "header.h"

typedef struct {

    int * vettore;

    /* TBD: Aggiungere altre variabili per la sincronizzazione */

} risorsa_database;


typedef struct {

    /* TBD: Utilizzare questa struttura dati per il
            passaggio dei parametri dal thread principale ai
            thread worker.
     */

} parametri_worker;


void * worker(void * x);


#define THREAD_WORKER 3


int main() {

    // risorsa gestita dal database (vettore di interi)

    risorsa_database * r = malloc(sizeof(risorsa_database));

    r->vettore = malloc(sizeof(int) * DIM_VETTORE);

    for(int i=0; i<DIM_VETTORE; i++) {
        r->vettore[i] = 0;
    }


    /* TBD: Completare l'inizializzazione delle variabili di sincronizzazione */



    /* TBD: Ottenere gli identificativi delle code di messaggi */



    /* TBD: Creare 3 thread worker, e utilizzare la struttura "parametri_worker"
            per passare ai thread il puntatore alla risorsa e gli
            identificativi delle code di messaggi.
     */

    for(int i=0; i<THREAD_WORKER; i++) {

        /* TBD */
    }

    /* TBD: Attendere la terminazione dei thread worker */



    free(r->vettore);
    free(r);

}



void * worker(void * x) {

    /* TBD: Completare il passaggio dei parametri */

    risorsa_database * r = /* TBD */;

    
    for(int i=0; i<NUMERO_RICHIESTE; i++) {

        /* TBD: Ricevere un messaggio di richiesta */

        int tipo_richiesta = /* TBD */;
        int valore = /* TBD */;
        int posizione = /* TBD */;
        int pid_server = /* TBD */;

        printf("[DB] Ricevuta richiesta (tipo=%d, pid=%d, posizione=%d, valore=%d)\n", tipo_richiesta, pid_server, posizione, valore);


        int valore_risposta;

        /* TBD: Aggiungere la sincronizzazione per l'accesso alla risorsa condivisa */

        if(/* TBD: Verificare se è una richiesta di LETTURA */) {

            valore_risposta = r->vettore[posizione];

        }
        else if(/* TBD: Verificare se è una richiesta di SCRITTURA */) {

            r->vettore[posizione] = valore;
            valore_risposta = 0;

        }
        else {
            printf("[DB] Tipo richiesta non valido\n");
        }



        /* TBD: Inviare un messaggio di risposta, includendo la variabile "valore_risposta" */

    }

    return NULL;

}