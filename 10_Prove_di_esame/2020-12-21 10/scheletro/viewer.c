#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"

int main(){
    
    //Creazione code richieste e risposte
    int ds_queue_request, ds_queue_response;

    //create queues
    int key_queue_request = // TODO aggiungere codice per la generazione della chiave
    int key_queue_response = // TODO aggiungere codice per la generazione della chiave
    
    // TODO aggiungere codice di inizializzazione delle code
    ds_queue_request = //...
    ds_queue_response = //...
    
    printf("[viewer] Coda ds_queue_request ID: %d\n", ds_queue_request);
    printf("[viwwer] Coda ds_queue_response ID: %d\n", ds_queue_response);
    
    
    Msg_Req m_req;
    Msg_Resp m_res;

   
    int i;

    srand(time(NULL)*getpid());
    
    for (i=0; i<4; i++){
        
        // TODO costruzione del messaggio di richiesta

        // TODO aggiungere codice per inviare la richiesta
        
        // TODO aggiungere codice per ricevere la risposta
        
        printf("[viewer] Sono disponibili %d unità del prodotto %d\n",m_res.scorta,m_res.id_prodotto);
    }
    
    return 0;
}


