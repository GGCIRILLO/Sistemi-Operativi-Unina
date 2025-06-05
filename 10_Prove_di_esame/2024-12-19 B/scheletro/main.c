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

    /*
        TODO: creazione thread produttori, consumatori e Babbo_Natale
    */

    /*
        TODO: attesa terminazione thread produttori, consumatori e Babbo_Natale
    */

    /*
        TODO: rimozione strutture
    */

    return 0;
}

void* Produttore(void* p) {
    for (int i = 0; i < GIOCATTOLI_PER_PROD; i++) {
        sleep(2);
        int giocattolo = rand() % 100 + 1;
        /*
            TODO: produzione e terminazione
        */
    }

}

// Thread consumatore
void* Consumatore(void* p) {


    for (int i=0; i<PRELIEVI_PER_CONS; i++) {
        /*
            TODO: consumo, aggiornamento e terminazione
        */
    }


}

// Thread Babbo Natale
void* Babbo_Natale(void* p) {

    for (int i=0; i<CONSEGNE; i++) {
        /*
            TODO: consegna e terminazione
        */
    }


}