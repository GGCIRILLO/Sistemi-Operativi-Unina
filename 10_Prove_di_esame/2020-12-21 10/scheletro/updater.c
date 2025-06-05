#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"

#define MAX_DECR 4;

int main(){
    
    //Creazione code richieste e risposte
    int ds_queue_request, ds_queue_response;

    //create queues
    int key_queue_request = // TODO aggiungere codice per la generazione della chiave
    int key_queue_response = // TODO aggiungere codice per la generazione della chiave
    
    // TODO aggiungere codice di inizializzazione delle code
    ds_queue_request = //...
    ds_queue_response = //...
    
    printf("[updater] Coda ds_queue_request ID: %d\n", ds_queue_request);
    printf("[updater] Coda ds_queue_response ID: %d\n", ds_queue_response);
    
    
    Msg_Req m_req;

   
    
    
    int i;

    srand(time(NULL)*getpid());
    
    for (i=0; i<2; i++){

        // TODO costruzione del messaggio di richiesta
        
        // TODO aggiungere codice per l'invio della richiesta

        printf("[updater] Richiesto decremento di %d unità del prodotto %d\n",m_req.value,m_req.id_prodotto);
    }
    
    return 0;
}


