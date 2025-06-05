#include <stdio.h>

#include "prodcons.h"


void init_monitor(MonitorProdCons * p) {

    /* TBD: Inizializzare l'oggetto monitor */

    p->conteggio_consumazioni = 0;
}

void produzione(MonitorProdCons * p, int val) {

    /* TBD: Completare la sincronizzazione, in base allo schema
            del vettore di buffer circolare */

    p->buffer[/*TBD*/] = val;

}

int consumazione(MonitorProdCons * p) {

    int val;

    /* TBD: Completare la sincronizzazione, in base allo schema
            del vettore di buffer circolare */

    val = p->buffer[/*TBD*/];

    p->conteggio_consumazioni++;

    return val;
}

int attendi_consumazioni(MonitorProdCons * p, int soglia) {

    int n;

    /* TBD: Sospendere il thread finché il "conteggio_consumazioni" non sia diventato
            maggiore o uguale a "soglia"
     */

    n = p->conteggio_consumazioni;

    p->conteggio_consumazioni = 0;
    
    return n;
}

void remove_monitor(MonitorProdCons * p) {

    /* TBD: Disattivare le variabili per la sincronizzazione */
}