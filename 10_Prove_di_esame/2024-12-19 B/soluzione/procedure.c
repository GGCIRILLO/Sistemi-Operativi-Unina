#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

void inizializza_coda(CodaCircolare *coda) {
    /*
        TODO: completare
    */
    coda->testa=0;
    coda->coda=0;
    coda->elementi=0;
    pthread_mutex_init(&coda->mutex, NULL);
    pthread_cond_init(&coda->cv_prod, NULL);
    pthread_cond_init(&coda->cv_cons, NULL);
}

void distruggi_coda(CodaCircolare *coda) {
    /*
        TODO: completare
    */
    pthread_mutex_destroy(&coda->mutex);
    pthread_cond_destroy(&coda->cv_prod);
    pthread_cond_destroy(&coda->cv_cons);
}


void produci(CodaCircolare *coda, int giocattolo) {
    /*
        TODO: produzione
    */
    pthread_mutex_lock(&coda->mutex);

    while(coda->elementi==DIM){
        pthread_cond_wait(&coda->cv_prod, &coda->mutex);
    }
    coda->buffer[coda->testa] = giocattolo;
    coda->testa = (coda->testa+1)%DIM;
    coda->elementi++;

    printf("Prodotto giocattolo: %d (count=%d)\n", giocattolo, coda->elementi);

    if (coda->elementi>=3) pthread_cond_signal(&coda->cv_cons);

    pthread_mutex_unlock(&coda->mutex);
}

void consuma(CodaCircolare *coda) {

    /*
        TODO: consumo di 3 giocattoli 
    */
    pthread_mutex_lock(&coda->mutex);

    while(coda->elementi<3){
        pthread_cond_wait(&coda->cv_cons, &coda->mutex);
    }

    for (int i=0;i<3;i++){
        int giocattolo = coda->buffer[coda->coda];
        coda->coda = (coda->coda+1)%DIM;
        coda->elementi--;

        printf("Prelevato giocattolo: %d (count=%d)\n", giocattolo, coda->elementi);

        pthread_cond_signal(&coda->cv_prod);
    }

    

    pthread_mutex_unlock(&coda->mutex);
}

void inizializza_buffer(BufferBabbo *buffer) {
    /*
        TODO: completare
    */
    buffer->consegne_effettuate=0;
    buffer->buffer_regali=0;
    pthread_mutex_init(&buffer->mutex, NULL);
    pthread_cond_init(&buffer->cv_babbo, NULL);
}

void distruggi_buffer(BufferBabbo *buffer) {
    /*
        TODO: completare
    */
    pthread_mutex_destroy(&buffer->mutex);
    pthread_cond_destroy(&buffer->cv_babbo);
}

void aggiorna_conteggio(BufferBabbo *buffer) {
    /*
        TODO: incremento buffer una volta consumati 3 giocattoli
    */
    pthread_mutex_lock(&buffer->mutex);

        buffer->buffer_regali++;

    printf("Regalo pronto: %d\n", buffer->buffer_regali);

    if (buffer->buffer_regali >= REGALI_PER_CONSEGNA){
        pthread_cond_signal(&buffer->cv_babbo);
    }

    pthread_mutex_unlock(&buffer->mutex);
    
}

void consegna(BufferBabbo *buffer) {

    /*
        TODO: consegna dei regali una volta impacchettati 5 regali
    */
    pthread_mutex_lock(&buffer->mutex);

    while(buffer->buffer_regali<5){
        pthread_cond_wait(&buffer->cv_babbo, &buffer->mutex);
    }
    buffer->consegne_effettuate++;

    buffer->buffer_regali -= 5;

    printf("Babbo Natale consegna effettuata #%d\n", buffer->consegne_effettuate);

    pthread_mutex_unlock(&buffer->mutex);

}
