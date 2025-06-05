#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

void inizializza_coda(CodaCircolare *coda) {
    /*
        TODO: completare
    */
}

void distruggi_coda(CodaCircolare *coda) {
    /*
        TODO: completare
    */
}


void produci(CodaCircolare *coda, int giocattolo) {
    /*
        TODO: produzione
    */
    printf("Prodotto giocattolo: %d (count=%d)\n", giocattolo, coda->count);

}

void consuma(CodaCircolare *coda) {

    /*
        TODO: consumo di 3 giocattoli 
    */
    
        printf("Prelevato giocattolo: %d (count=%d)\n", giocattolo, coda->count);

}

void inizializza_buffer(BufferBabbo *buffer) {
    /*
        TODO: completare
    */
}

void distruggi_buffer(BufferBabbo *buffer) {
    /*
        TODO: completare
    */
}

void aggiorna_conteggio(BufferBabbo *buffer) {
    /*
        TODO: incremento buffer una volta consumati 3 giocattoli
    */

    printf("Regalo pronto: %d\n", buffer->buffer_regali);

    
}

void consegna(BufferBabbo *buffer) {

    /*
        TODO: consegna dei regali una volta impacchettati 5 regali
    */

    buffer->buffer_regali -= 5;

    printf("Babbo Natale consegna effettuata #%d\n", buffer->consegne_effettuate);

}
