#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"
#include "store.h"

#define MAX_DECR 4;

int main(){
    
    //Creazione code richieste e risposte
    int ds_queue_request, ds_queue_response;

    //create queues
    int key_queue_request = ftok(".", 'A'); // TODO aggiungere codice per la generazione della chiave
    int key_queue_response = ftok(".", 'B'); // TODO aggiungere codice per la generazione della chiave
    if (key_queue_request <0 || key_queue_response<0 ) die("ftok updater");

    // TODO aggiungere codice di inizializzazione delle code
    ds_queue_request = msgget(key_queue_request, 0); //...
    ds_queue_response = msgget(key_queue_response, 0); //...
    if (ds_queue_request<0 || ds_queue_response<0 ) die("msgget updater");
    
    printf("[updater] Coda ds_queue_request ID: %d\n", ds_queue_request);
    printf("[updater] Coda ds_queue_response ID: %d\n", ds_queue_response);
    
    
    Msg_Req m_req;

    m_req.tipo_richiesta = WRITE;
    m_req.mittente = getpid();
    
    
    int i;

    srand(time(NULL)*getpid());
    
    for (i=0; i<2; i++){

        // TODO costruzione del messaggio di richiesta
        m_req.id_prodotto = rand()%MAX_PRODOTTI;
        m_req.value = rand()%MAX_DECR +1;
        
        // TODO aggiungere codice per l'invio della richiesta
        int ret = msgsnd(ds_queue_request, (void*)&m_req, sizeof(m_req)-sizeof(long), 0);
        if (ret<0) die("msgsnd updt");

        printf("[updater] Richiesto decremento di %d unità del prodotto %d\n",m_req.value,m_req.id_prodotto);
    }
    
    return 0;
}


