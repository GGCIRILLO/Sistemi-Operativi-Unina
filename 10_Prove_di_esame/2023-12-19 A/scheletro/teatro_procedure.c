#include <stdio.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "teatro.h"

void * clientT(void *m){
    
    /* TODO: ottenre il riferimento al monitor */
    
    
    int i, ID_posto, tipo_posto;
    posto_teatro posto;
    
    
    for(i=0; i<10; i++) {
        
        posto.ID = rand() % 100;
        posto.tipo = rand() % 2;
        
        /* TODO: operazione di scrittura */
        sleep(1);
    }
    
    pthread_exit(NULL);
}

void * viewerT(void *m){
    
    /* TODO: ottenre il riferimento al monitor */
    
    int i;
    
    int ds_queue_viewer;
    
    //create queues
    int key_queue_viewer = /* TODO: ottenere chiave per la coda di comunicazione tra viewers e report */
    
    ds_queue_viewer = /* TODO: ottenere il descrittore per la coda di comunicazione tra viewers e report */
    
    printf("[viewerT] Coda ds_queue_viewer ID: %d\n", ds_queue_viewer);
    
    for(i=0; i<4; i++) {
        
        /* TODO: operazione di lettura */
        sleep(1);
    
    }
    
    pthread_exit(NULL);
    
}

void scrivi_posto(LettScritt *ls, posto_teatro *posto){
    
    /* TODO */
    
    ls->p->ID = posto->ID;
    ls->p->tipo = posto->tipo;
    
    printf("Thread Client - Posto SCRITTO ID = %d tipo = %d\n", ls->p->ID, ls->p->tipo);
    
    /* TODO */
}

void leggi_posto(LettScritt *ls, int ds_queue_viewer){
    
    /* TODO */
    
    printf("Thread Client - Posto LETTO ID = %d tipo = %d\n", ls->p->ID, ls->p->tipo);

    //invio messaggio a report
    Msg_Posto posto_msg;
    int ret;
    
    /* TODO: impostare il messaggio posto_msg da inviare */
    
    /* TODO */
    // invio messaggio
    
    ret = /* TODO: invio messaggio sulla coda */
    if (ret<0){
        perror("msgsnd leggi_posto FALLITA!");
        exit(-1);
    }
    printf("[leggi_posto] Messaggio posto: %d INVIATO!\n", posto_msg.value);

    
    
}

/* Metodi privati del monitor */

void InizioLetturaPosto(LettScritt * ls){
    /* TODO: implementare la routine di inizio lettura considerando la strategia
     starvation di entrambi i lettori e scrittori */
}

void FineLetturaPosto(LettScritt * ls){
    
    /* TODO: implementare la routine di fine lettura considerando la strategia
     starvation di entrambi i lettori e scrittori */
}


void InizioScritturaPosto(LettScritt * ls){
    
    /* TODO: implementare la routine di inizio scrittura considerando la strategia
     starvation di entrambi i lettori e scrittori */
}

void FineScritturaPosto (LettScritt * ls){
    
    /* TODO: implementare la routine di fine scrittura considerando la strategia
        starvation di entrambi i lettori e scrittori
     */
}
