#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "header.h"

void inizializza_coda(MonitorPC *pc) {
/*
    TODO: completare
*/
}

void rimuovi_coda(MonitorPC *pc) {
/*
    TODO: completare
*/
}

void produci(MonitorPC *pc, Lettera lettera) {
/*
    TODO: completare produzione con coda circolare
*/

    printf("[Produttore %d] Ho inviato lettera: ID=%d, regali=%d\n", getpid(), lettera.id_bambino, lettera.numero_regali);

}

Lettera consuma(MonitorPC *pc) {
    Lettera lettera;
/*
    TODO: completare consumo con coda circolare
*/
    return lettera;
}

void SendSincr (MessaggioRispostaBabbo *mess, int queue){
/*
    TODO: completare
*/
}

void ReceiveBloc(MessaggioRispostaBabbo *mess, int queue){
/*
    TODO: completare
*/
}

void Produttore(MonitorPC *pc, int id_bambino, int coda_risposte) {
    /*
        TODO: completare inizializzazione lettera e produzione
    */
    Lettera lettera;

    /*
        TODO: attesa risposta
    */

    printf("[Produttore %d] Risposta ricevuta: %s\n", getpid(), risposta.messaggio);
}

void Consumatore(MonitorPC *pc, int coda_risposte) {
    int cattivi[] = {3, 5, 7, 9};
    int num_cattivi = sizeof(cattivi) / sizeof(cattivi[0]);

    for (int i=0; i<NUM_BAMBINI; i++) {
        /*
            TODO: completare consumo di una lettera
        */
        printf("[Babbo Natale] Ho ricevuto una lettera con ID=%d e regali=%d\n", lettera.id_bambino, lettera.numero_regali);

        /*
            TODO: creazione messaggio di risposta, controllo dell'id e invio del messaggio di risposta
        */

        printf("[Babbo Natale] Il bambino è stato %s\n", risposta.messaggio);

        sleep(1);
    }
}

void controlla_buono(MessaggioRispostaBabbo *risposta, int id, int *cattivi) {
    strcpy(risposta->messaggio, "buono");
    for (int i = 0; i < NUM_CATTIVI; i++) {
        if (cattivi[i] == id) {
            strcpy(risposta->messaggio, "cattivo");
            break; 
        }
    }
}

