#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "header.h"

typedef struct {
    MonitorLettScritt * ls;
    int regali_richiesti;
} ParametriScrittore;

int coda_richieste;
int coda_risposte;

void inizializza_struttura(MonitorLettScritt * ls) {
    /*
        TODO: completare
    */
}

void distruggi_struttura(MonitorLettScritt *ls) {
    /*
        TODO: completare
    */
}

void inizio_lettura(MonitorLettScritt *ls) {
    /*
        TODO: completare
    */
}

void fine_lettura(MonitorLettScritt *ls) {
    /*
        TODO: completare
    */
}

void inizio_scrittura(MonitorLettScritt *ls) {
    /*
        TODO: completare
    */
}

void fine_scrittura(MonitorLettScritt *ls) {
    /*
        TODO: completare
    */
}

void *Scrittore(void *arg) {
    /*
        TODO: recupero parametri thread e inizio scrittura
    */


    ls->totale_regali += ps->regali_richiesti;

    printf("Il totale dei regali richiesti finora è: %d\n", ls->totale_regali);

    /*
        TODO: completare
    */

    pthread_exit(NULL);
}

void *Lettore(void *arg) {
    /*
        TODO: recupero parametri thread
    */

    sleep(3);


    printf("[Lettore] Il totale di regali da consegnare è: %d\n", ls->totale_regali);


    /*
        TODO: invio messaggio di risposta
    */

    printf("Ho inviato conferma di ricezione al bambino\n");

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    /*
        TODO: recupero code e inizializzazione strutture
    */

    ParametriScrittore parametri[NUM_BAMBINI*NUM_LETTERE];

    pthread_t /* TODO */

    for (int i = 0; i < NUM_BAMBINI*NUM_LETTERE; i++) 
        /* TODO */

    MessaggioRichiesta msg;
    for (int i = 0; i < NUM_BAMBINI*NUM_LETTERE; i++) {
        msgrcv(coda_richieste,&msg,sizeof(MessaggioRichiesta)-sizeof(long),0,0);
        /*
            TODO: ricezione messaggio, inizializzazione della struttura parametri da passare al thread e creazione scrittore
        */
        printf("Ho ricevuto una letterina! Sono richiesti %d regali\n", msg.numero_regali);

    }


    /*
        TODO: attendo terminazione thread e dealloco strutture
    */

    return 0;

}