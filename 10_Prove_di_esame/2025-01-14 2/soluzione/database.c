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
    pthread_mutex_t mutex;

} risorsa_database;


typedef struct {

    /* TBD: Utilizzare questa struttura dati per il
            passaggio dei parametri dal thread principale ai
            thread worker.
     */
    int id_coda_req_serv_db;

    int id_coda_res_serv_db;

    risorsa_database * r;

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
    pthread_mutex_init(&r->mutex, NULL);


    /* TBD: Ottenere gli identificativi delle code di messaggi */
    key_t k_req_serv_db = ftok(".", 'c');
    if (k_req_serv_db<0) die("ftok");

    int id_coda_req_serv_db = msgget(k_req_serv_db, 0);
    if (id_coda_req_serv_db<0) die("msgget");    

    key_t k_res_serv_db = ftok(".", 'd');
    if (k_res_serv_db<0) die("ftok");

    int id_coda_res_serv_db = msgget(k_res_serv_db, 0);
    if (id_coda_res_serv_db<0) die("msgget");


    /* TBD: Creare 3 thread worker, e utilizzare la struttura "parametri_worker"
            per passare ai thread il puntatore alla risorsa e gli
            identificativi delle code di messaggi.
     */ 
    parametri_worker parametri[THREAD_WORKER];
    pthread_t threads[THREAD_WORKER];

    for(int i=0; i<THREAD_WORKER; i++) {

        /* TBD */
        parametri[i].id_coda_req_serv_db = id_coda_req_serv_db;
        parametri[i].id_coda_res_serv_db = id_coda_res_serv_db;
        parametri[i].r = r;

        pthread_create(&threads[i], NULL, worker, (void*)&parametri[i]);
    }

    /* TBD: Attendere la terminazione dei thread worker */
    for (int i=0;i<THREAD_WORKER;i++){
        pthread_join(threads[i], NULL);
    }


    free(r->vettore);
    free(r);

}



void * worker(void * x) {

    /* TBD: Completare il passaggio dei parametri */
    parametri_worker * p = (parametri_worker*) x;

    risorsa_database * r = p->r /* TBD */;
    int ret;
    
    for(int i=0; i<NUMERO_RICHIESTE; i++) {

        /* TBD: Ricevere un messaggio di richiesta */
        messaggio_richiesta m;
        ret = msgrcv(p->id_coda_req_serv_db, (void*)&m, sizeof(m)-sizeof(long), 0, 0);
        if (ret<0) die("msgrcv");

        int tipo_richiesta = m.tipo /* TBD */;
        int valore = m.valore/* TBD */;
        int posizione = m.posizione /* TBD */;
        int pid_server = m.pid_mittente /* TBD */;

        printf("[DB] Ricevuta richiesta (tipo=%d, pid=%d, posizione=%d, valore=%d)\n", tipo_richiesta, pid_server, posizione, valore);


        int valore_risposta;

        /* TBD: Aggiungere la sincronizzazione per l'accesso alla risorsa condivisa */
        pthread_mutex_lock(&r->mutex);

        if(tipo_richiesta==LETTURA /* TBD: Verificare se è una richiesta di LETTURA */) {

            valore_risposta = r->vettore[posizione];

        }
        else if(tipo_richiesta == SCRITTURA /* TBD: Verificare se è una richiesta di SCRITTURA */) {

            r->vettore[posizione] = valore;
            valore_risposta = 0;

        }
        else {
            printf("[DB] Tipo richiesta non valido\n");
        }

        pthread_mutex_unlock(&r->mutex);



        /* TBD: Inviare un messaggio di risposta, includendo la variabile "valore_risposta" */
        messaggio_risposta msg;
        msg.tipo = pid_server;
        msg.valore = valore_risposta;
        ret = msgsnd(p->id_coda_res_serv_db, (void*)&msg, sizeof(messaggio_risposta)-sizeof(long), 0);
        if (ret<0);

        printf("[DB] Invio risposta (tipo=%d, pid=%d, posizione=%d, valore=%d)\n", tipo_richiesta, pid_server, posizione, valore_risposta);
    }

    pthread_exit(NULL);

    return NULL;

}