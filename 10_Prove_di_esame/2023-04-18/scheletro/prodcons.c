#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "prodcons.h"

void inizializza(MonitorPC * m) {

    printf("Inizializzazione monitor\n");

    /* TBD: Inizializzazione */

}


void rimuovi(MonitorPC * m) {

    printf("Rimozione monitor\n");

    /* TBD: Rimozione */

}


void produci_tipo_1(MonitorPC * m, int valore) {

    int index = 0;

    /* TBD: Aggiungere la sincronizzazione, 
            con la selezione dell'indice su cui produrre
            (alg. con vettore di stato) */

    printf("Produzione di tipo 1 in corso (valore=%d, index=%d)\n", valore, index);

    sleep(1);
    m->vettore[index] = valore;

}


void produci_tipo_2(MonitorPC * m, int valore) {

    int index = 0;

    /* TBD: Aggiungere la sincronizzazione, 
        con la selezione dell'indice su cui produrre
        (alg. con vettore di stato) */

    printf("Produzione di tipo 2 in corso (valore=%d, index=%d)\n", valore, index);

    sleep(1);
    m->vettore[index] = valore;
}


void consuma_tipo_1(MonitorPC * m, int * valore) {

    int index = 0;

    /* TBD: Aggiungere la sincronizzazione, 
        con la selezione dell'indice su cui consumare
        (alg. con vettore di stato) */

    sleep(1);
    *valore = m->vettore[index];

    printf("Consumazione di tipo 1 (valore=%d, index=%d)\n", *valore, index);
}


void consuma_tipo_2(MonitorPC * m, int * valore) {

    int index = 0;

    /* TBD: Aggiungere la sincronizzazione, 
        con la selezione dell'indice su cui consumare
        (alg. con vettore di stato) */

    sleep(1);
    *valore = m->vettore[index];

    printf("Consumazione di tipo 2 (valore=%d, index=%d)\n", *valore, index);
}