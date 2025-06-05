#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>

#include "store.h"

extern int ds_queue_request, ds_queue_response;

void Wait_Sem(int ds_sem, int id_sem) {
    struct sembuf buf;
    buf.sem_flg = 0;
    buf.sem_num = id_sem;
    buf.sem_op = -1;
    semop(ds_sem,&buf,1);
}

void Signal_Sem(int ds_sem, int id_sem) {
    struct sembuf buf;
    buf.sem_flg = 0;
    buf.sem_num = id_sem;
    buf.sem_op = 1;
    semop(ds_sem,&buf,1);
}

void init_magazzino(Magazzino *magazzino){
    // TODO inizializzazione dei semafori , delle variabili necessarie alla sincronizzazione
    // e delle scorte di magazzino iniziali
   
}
void destroy_magazzino(Magazzino *magazzino){
    // TODO rimozione dei semafori
}

void lettore(Magazzino *magazzino) {
    int ret;
    Msg_Req m_req;
    Msg_Resp m_resp;
    int k;

    for (k=0; k<4; k++) {
        // TODO aggiungere codice per la ricezione comando
        

        // TODO Aggiungere codice per la lettura:
        // InizioLettura
        // Lettura del livello di scorta del prodotto il cui id è indicato nella richiesta
        // FineLettura

        // TODO Costruire il messaggio di risposta m_resp

        printf("[lettore] Ricevuta richiesta di lettura per prodotto %d con livello scorte %d\n",m_resp.id_prodotto,m_resp.scorta);

        // TODO aggiungere codice per l'invio del messaggio di risposta
    }
}

void scrittore(Magazzino *magazzino){
    int ret;
    Msg_Req m_req;
    int k;

    for (k = 0; k < 2; k++) {
        // TODO agiungere codice per la ricezione del comando
        

        // TODO aggiungere codice per la scrittura
        // InizioScrittura
        // Decremento del livello di scorta del prodotto indicato nella richiesta della quantità indicata nella richiesta
        // FineScrittura

        printf("[scrittore] Ricevuta richiesta di decremento di %d per prodotto %d\n",m_req.value, m_req.id_prodotto);
    }
}

void InizioLettura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di inizio lettura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
}

void FineLettura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di fine lettura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
}

void InizioScrittura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di inizio scrittura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
}
void FineScrittura(Magazzino *magazzino, int id_prodotto){
    //TODO aggiungere il codice di fine scrittura, utilizzando i semafori
    // secondo lo schema lettori-scrittori con starvation degli scrittori
}
