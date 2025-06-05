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
    
    pthread_t client_threads[2];
    pthread_t viewer_threads[5];
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    
    srand(time(NULL)*getpid());
    
    posto_teatro *p = (posto_teatro*) malloc(sizeof(posto_teatro)); /* TODO: allocare memoria per il buffer condiviso */
    LettScritt *m = (LettScritt*) malloc(sizeof(LettScritt)); /* TODO: allocare memoria per il monitor */
    
    /* TODO: inizializzazione variabili da usare durante la sincronizzazione */
    m->p = p;
    m->lettori = 0;
    m->scrittori = 0;
    m->lettori_in_attesa = 0;
    m->scrittori_in_attesa = 0;
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cv_lettura, NULL);
    pthread_cond_init(&m->cv_scrittura, NULL);

    printf("[teatro] Creazione dei thread client e viewer\n");
    
    //creazione dei threads client, totale scritture 2* 10 = 20
    for(i=0;i<2;i++){
        /* TODO: creare i thread clients */
        pthread_create(&client_threads[i], &attr, clientT, (void*)m);
    }
    
    //creazione dei threads viewer, totali letture 5*4 = 20
    for(i=0;i<5;i++){
        /* TODO: creare i thread viewers */
        pthread_create(&viewer_threads[i], &attr, viewerT, (void*)m);
    }
    
    //join dei threads clients
    for(i=0;i<2;i++){
        /* TODO: attendere la terminazione dei thread clients */
        pthread_join(client_threads[i], NULL);
        printf("client_threads %d terminato\n",i+1);
    }
    
    //join dei threads viewers
    for(i=0;i<5;i++){
        /* TODO: attendere la terminazione dei thread viewers */
        pthread_join(viewer_threads[i], NULL);
        printf("viewer_threads %d terminato\n",i+1);
    }
    
    //deallocazione monitor
    /* TODO: deallocazione variabili usate durante la sincronizzazione */
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->cv_lettura);
    pthread_cond_destroy(&m->cv_scrittura);
    free(m->p); 
    free(m); 
    
    pthread_exit(NULL);
}

