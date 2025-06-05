#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include "header.h"

#define NUM_VIEWERS 3
#define NUM_UPDATERS 2


int main(){

    pid_t pid;
    int status, k;
    
    //Creazione code richieste e risposte
    int ds_queue_request, ds_queue_response;

    //create queues
    int key_queue_request = // TODO aggiungere codice per la generazione della chiave
    int key_queue_response = // TODO aggiungere codice per la generazione della chiave
    
    // TODO aggiungere codice di inizializzazione delle code
    ds_queue_request = //...
    ds_queue_response = //...
    
    printf("[master] Coda ds_queue_request creata! ID: %d\n", ds_queue_request);
    printf("[master] Coda ds_queue_response creata! ID: %d\n", ds_queue_response);
    
    // TODO aggiungere codice per generare NUM_VIEWERS processi viewers, attraverso l'exec
    

    // TODO aggiungere codice per generare NUM_UPDATERS processi updaters, attraverso l'exec
    

    // TODO aggiungere codice per generare 1 processo store, attraverso l'exec
    
    for (k=0; k<NUM_VIEWERS+NUM_UPDATERS+1; k++){
        pid = wait(&status);
        if (pid == -1)
            perror("errore");
        else
            printf ("[master] Figlio n.ro %d e\' morto con status= %d \n", pid, status);
    }

    // TODO aggiungere codice per la rimozione delle code

    printf("[master] code rimosse\n");
    
    return 0;
}
