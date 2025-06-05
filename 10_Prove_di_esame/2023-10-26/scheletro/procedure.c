#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"


void init_monitor(MonitorIO * m) {

    /* TBD: Inizializzare l'oggetto monitor */
}

void end_monitor(MonitorIO * m) {

    /* TBD: Disattivare le variabili membro dell'oggetto monitor */
}

void produzione(MonitorIO * m, char c) {

    int i;

    /* TBD: Porre il thread in sospensione se il vettore di buffer è pieno */

    /* TBD: Ricercare un elemento "i" nello stato LIBERO,
            in base allo schema con vettore di stato       */



    printf("PRODUZIONE: inizio produzione vettore[%d]\n", i);
    sleep(1 + (rand() % 3));
    m->vettore[i] = c;
    printf("PRODUZIONE: vettore[%d] <- '%c'\n", i, c);



    /* TBD: Riattivare un thread consumatore sospeso */

    /* TBD: Riattivare i thread sospesi sulla variabile condition "cv_attesa" */
}

char consumazione(MonitorIO * m) {

    int i;

    /* TBD: Porre il thread in sospensione se il vettore di buffer è vuoto */

    /* TBD: Ricercare un elemento "i" nello stato OCCUPATO,
            in base allo schema con vettore di stato       */



    printf("CONSUMAZIONE: inizio consumazione vettore[%d]\n", i);
    sleep(1);
    char c = m->vettore[i];
    printf("CONSUMAZIONE: vettore[%d] -> '%c'\n", i, c);



    /* TBD: Riattivare un thread produttore sospeso */

    return c;
}

int attesa(MonitorIO * m) {

    int occupati;

    /* TBD: Se il numero di buffer occupati è minore di 3,
     *      sospendere il thread sulla condition variable "cv_attesa" */

    occupati = /* TBD: Restituire in uscita il numero di buffer occupati */

    return occupati;
}
