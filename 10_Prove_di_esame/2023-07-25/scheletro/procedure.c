#include <stdio.h>

#include "procedure.h"

void inizializza(MonitorPortafoglio * m, int quantita_iniziale, int valore_iniziale) {

    /* TBD: Inizializzare l'oggetto monitor */
}

void termina(MonitorPortafoglio * m) {

    /* TBD: De-inizializzare l'oggetto monitor */
}

void acquisto(MonitorPortafoglio * m, int quantita, int prezzo) {

    /* TBD: Aggiungere la sincronizzazione */

    m->quantita += quantita;

}

void vendita(MonitorPortafoglio * m, int quantita, int prezzo) {

    /* TBD: Aggiungere la sincronizzazione */

    m->quantita -= quantita;

}

void aggiorna(MonitorPortafoglio * m, int valore) {

    /* TBD: Aggiungere la sincronizzazione */

    m->valore = valore;
}

int leggi(MonitorPortafoglio * m) {

    /* TBD: Aggiungere la sincronizzazione */

    int valore;

    valore = m->valore;

    return valore;
}