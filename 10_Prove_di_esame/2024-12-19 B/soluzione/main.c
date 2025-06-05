#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "header.h"

CodaCircolare coda;

int main() {
    srand(time(NULL));

    /*
        TODO: allocazione buffer e inizializzazione strutture
    */

    inizializza_coda(&coda);

    BufferBabbo* b = (BufferBabbo*) malloc(sizeof(BufferBabbo));
    inizializza_buffer(b);


    /*
        TODO: creazione thread produttori, consumatori e Babbo_Natale
    */
    pthread_t threads_prod[NPROD];
    for(int i=0;i<NPROD;i++){
        pthread_create(&threads_prod[i], NULL, Produttore, NULL);
    }

    pthread_t threads_cons[NCONS];
    for(int i=0;i<NCONS;i++){
        pthread_create(&threads_cons[i], NULL, Consumatore, (void*)b);
    }

    pthread_t thread_babbo;
    pthread_create(&thread_babbo, NULL, Babbo_Natale, (void*)b);

    /*
        TODO: attesa terminazione thread produttori, consumatori e Babbo_Natale
    */
    for (int i=0;i<NPROD;i++){
        pthread_join(threads_prod[i], NULL);
    }
    for (int i=0;i<NCONS;i++){
        pthread_join(threads_cons[i], NULL);
    }

    pthread_join(thread_babbo, NULL);

    /*
        TODO: rimozione strutture
    */
    distruggi_coda(&coda);

    distruggi_buffer(b);
    free(b);

    return 0;
}

void* Produttore(void* p) {
    for (int i = 0; i < GIOCATTOLI_PER_PROD; i++) {
        sleep(2);
        int giocattolo = rand() % 100 + 1;
        /*
            TODO: produzione e terminazione
        */
        produci(&coda, giocattolo);
    }
    pthread_exit(NULL);
}

// Thread consumatore
void* Consumatore(void* p) {

    BufferBabbo* b = (BufferBabbo*)p;

    for (int i=0; i<PRELIEVI_PER_CONS; i++) {
        /*
            TODO: consumo, aggiornamento e terminazione
        */
        consuma(&coda);
        aggiorna_conteggio(b);
    }
    pthread_exit(NULL);
}

// Thread Babbo Natale
void* Babbo_Natale(void* p) {

    BufferBabbo* b = (BufferBabbo*)p;

    for (int i=0; i<CONSEGNE; i++) {
        /*
            TODO: consegna e terminazione
        */
        consegna(b);
    }

    pthread_exit(NULL);

}