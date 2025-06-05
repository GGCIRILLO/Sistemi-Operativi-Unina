#include "monitor_fifo.h"

#include <stdio.h>
#include <unistd.h>

void inizializza(MonitorProdConsFIFO * p) {

    /* TBD: Inizializzare la struttura dati */
}

void produci(MonitorProdConsFIFO * p, int valore) {

    /* TBD: Completare con la sincronizzazione */

    int arrivo = p->ultimo_produttore_arrivato;

    p->ultimo_produttore_arrivato++;

    printf("[PRODUTTORE %d] Il mio turno di arrivo è %d\n", getpid(), arrivo);


    // ... gestire le condizioni di attesa ...


    printf("[PRODUTTORE %d] Il mio turno di produzione è %d\n", getpid(), p->ultimo_produttore_avviato);

    p->ultimo_produttore_avviato++;


    p->buffer[/* TBD */] = valore;

    sleep(1);

}

int consuma(MonitorProdConsFIFO * p) {

    /* TBD: Completare con la sincronizzazione */

    printf("[CONSUMATORE %d] Consumazione in corso\n", getpid());

    int valore = p->buffer[/* TBD */];

    sleep(1);


    /* Nota: Occorre riattivare -tutti- i produttori in attesa.
             Il numero di produttori in attesa è dato dalla seguente differenza.
     */

    int produttori_in_attesa = p->ultimo_produttore_arrivato - p->ultimo_produttore_avviato;


    return valore;
}

void distruggi(MonitorProdConsFIFO * p) {

    /* TBD: Disattivare l'oggetto monitor */
}
