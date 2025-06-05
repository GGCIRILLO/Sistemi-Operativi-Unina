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
    LettScritt * ls = (LettScritt*)m;
    
    
    int i, ID_posto, tipo_posto;
    posto_teatro posto;
    
    
    for(i=0; i<10; i++) {
        
        posto.ID = rand() % 100;
        posto.tipo = rand() % 2;
        
        /* TODO: operazione di scrittura */
        scrivi_posto(ls, &posto);
        sleep(1);
    }
    
    pthread_exit(NULL);
}

void * viewerT(void *m){
    
    /* TODO: ottenre il riferimento al monitor */
    LettScritt * ls = (LettScritt*)m;

    int i;
    
    int ds_queue_viewer;
    
    //create queues
    int key_queue_viewer = ftok(".", 'c'); /* TODO: ottenere chiave per la coda di comunicazione tra viewers e report */
    if (key_queue_viewer<0) die("ftok");

    ds_queue_viewer = msgget(key_queue_viewer, 0); /* TODO: ottenere il descrittore per la coda di comunicazione tra viewers e report */
    if (ds_queue_viewer<0) die("msgget");
    
    printf("[viewerT] Coda ds_queue_viewer ID: %d\n", ds_queue_viewer);
    
    for(i=0; i<4; i++) {
        
        /* TODO: operazione di lettura */
        leggi_posto(ls, ds_queue_viewer);
        sleep(1);
    
    }
    
    pthread_exit(NULL);
    
}

void scrivi_posto(LettScritt *ls, posto_teatro *posto){
    
    /* TODO */
    InizioScritturaPosto(ls);
    
    ls->p->ID = posto->ID;
    ls->p->tipo = posto->tipo;
    
    printf("Thread Client - Posto SCRITTO ID = %d tipo = %d\n", ls->p->ID, ls->p->tipo);
    
    /* TODO */
    FineScritturaPosto(ls);
}

void leggi_posto(LettScritt *ls, int ds_queue_viewer){
    
    /* TODO */
    InizioLetturaPosto(ls);
    
    printf("Thread Viewer - Posto LETTO ID = %d tipo = %d\n", ls->p->ID, ls->p->tipo);

    //invio messaggio a report
    Msg_Posto posto_msg;
    int ret;
    
    /* TODO: impostare il messaggio posto_msg da inviare */
    posto_msg.value = ls->p->tipo;
    posto_msg.tipo = 1;

    FineLetturaPosto(ls);
    
    /* TODO */
    // invio messaggio
    
    ret = msgsnd(ds_queue_viewer, (void*)&posto_msg, sizeof(Msg_Posto)-sizeof(long), 0); /* TODO: invio messaggio sulla coda */
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
    pthread_mutex_lock(&ls->mutex);

    while(ls->scrittori>0){
        ls->lettori_in_attesa++;
        pthread_cond_wait(&ls->cv_lettura, &ls->mutex);
        ls->lettori_in_attesa--;
    }

    ls->lettori++;

    pthread_mutex_unlock(&ls->mutex);
}

void FineLetturaPosto(LettScritt * ls){
    
    /* TODO: implementare la routine di fine lettura considerando la strategia
     starvation di entrambi i lettori e scrittori */
    pthread_mutex_lock(&ls->mutex);

    ls->lettori--;

    if (ls->lettori==0){
        pthread_cond_signal(&ls->cv_scrittura);
    }

    pthread_mutex_unlock(&ls->mutex);
}


void InizioScritturaPosto(LettScritt * ls){
    
    /* TODO: implementare la routine di inizio scrittura considerando la strategia
     starvation di entrambi i lettori e scrittori */
    pthread_mutex_lock(&ls->mutex);

    while(ls->lettori>0 || ls->scrittori>0){
        ls->scrittori_in_attesa++;
        pthread_cond_wait(&ls->cv_scrittura, &ls->mutex);
        ls->scrittori_in_attesa--;
    }

    ls->scrittori++;

    pthread_mutex_unlock(&ls->mutex);
}

void FineScritturaPosto (LettScritt * ls){
    
    /* TODO: implementare la routine di fine scrittura considerando la strategia
        starvation di entrambi i lettori e scrittori
     */
    pthread_mutex_lock(&ls->mutex);

    ls->scrittori--;

    if (ls->scrittori_in_attesa>0){
        pthread_cond_signal(&ls->cv_scrittura);
    } else {
        pthread_cond_broadcast(&ls->cv_lettura);
    }

    pthread_mutex_unlock(&ls->mutex);
}
