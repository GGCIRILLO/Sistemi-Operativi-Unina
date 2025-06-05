#include <stdio.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "teatro.h"


int main(){
    
    int i;
    
    pthread_t client_threads[10];
    pthread_t viewer_threads[10];
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    
    srand(time(NULL)*getpid());
    
    posto_teatro *p = /* TODO: allocare memoria per il buffer condiviso */
    LettScritt *m = /* TODO: allocare memoria per il monitor */
    
    /* TODO: inizializzazione variabili da usare durante la sincronizzazione */
    
    printf("[teatro] Creazione dei thread client e viewer\n");
    
    //creazione dei threads client, totale scritture 2* 10 = 20
    for(i=0;i<2;i++){
        /* TODO: creare i thread clients */
    }
    
    //creazione dei threads viewer, totali letture 5*4 = 20
    for(i=0;i<5;i++){
        /* TODO: creare i thread viewers */
    }
    
    //join dei threads clients
    for(i=0;i<2;i++){
        /* TODO: attendere la terminazione dei thread clients */
        printf("client_threads %d terminato\n",i+1);
    }
    
    //join dei threads viewers
    for(i=0;i<5;i++){
        /* TODO: attendere la terminazione dei thread viewers */
        printf("viewer_threads %d terminato\n",i+1);
    }
    
    //deallocazione monitor
    /* TODO: deallocazione variabili usate durante la sincronizzazione */
    
    pthread_exit(NULL);
}

