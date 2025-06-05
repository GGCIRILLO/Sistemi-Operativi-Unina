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
    pc->testa=0;
    pc->coda=0;
    pc->count=0;

    init_monitor(&pc->m, 2);
}

void rimuovi_coda(MonitorPC *pc) {
/*
    TODO: completare
*/
    remove_monitor(&pc->m);
}

void produci(MonitorPC *pc, Lettera lettera) {
/*
    TODO: completare produzione con coda circolare
*/
    enter_monitor(&pc->m);

    while(pc->count==DIM){
        wait_condition(&pc->m, CV_PROD);
    }

    pc->buffer[pc->testa] = lettera;
    pc->testa = (pc->testa+1)%DIM;
    pc->count++;

    signal_condition(&pc->m, CV_CONS);

    leave_monitor(&pc->m);

    printf("[Produttore %d] Ho inviato lettera: ID=%d, regali=%d\n", getpid(), lettera.id_bambino, lettera.numero_regali);

}

Lettera consuma(MonitorPC *pc) {
    Lettera lettera;
/*
    TODO: completare consumo con coda circolare
*/
    enter_monitor(&pc->m);

    while(pc->count==0){
        wait_condition(&pc->m, CV_CONS);
    }

    lettera = pc->buffer[pc->coda];
    pc->coda = (pc->coda+1)%DIM;
    pc->count--;

    signal_condition(&pc->m, CV_PROD);

    leave_monitor(&pc->m);

    return lettera;
}

void SendSincr (MessaggioRispostaBabbo *mess, int queue){
/*
    TODO: completare
*/
    MessaggioRispostaBabbo m1, m2;
    m1.tipo = RTS;
    int ret = msgsnd(queue, (void*)&m1, sizeof(MessaggioRispostaBabbo)-sizeof(long), 0);
    if (ret<0) die("msgsnd");

    ret = msgrcv(queue, (void*)&m2, sizeof(MessaggioRispostaBabbo)-sizeof(long), OTS, 0);
    if (ret<0) die("msgrcv");

    mess->tipo = MESS;
    ret = msgsnd(queue, (void*)mess, sizeof(MessaggioRispostaBabbo)-sizeof(long), 0);
    if (ret<0) die("msgsnd");
}

void ReceiveBloc(MessaggioRispostaBabbo *mess, int queue){
/*
    TODO: completare
*/
    MessaggioRispostaBabbo m1, m2;
    int ret = msgrcv(queue, (void*)&m1, sizeof(MessaggioRispostaBabbo)-sizeof(long), RTS, 0);
    if (ret<0) die("msgcrv");

    m2.tipo=OTS;
    ret = msgsnd(queue, (void*)&m2, sizeof(MessaggioRispostaBabbo)-sizeof(long), 0);
    if (ret<0) die("msgsnd");

    ret = msgrcv(queue, (void*)mess, sizeof(MessaggioRispostaBabbo)-sizeof(long), MESS, 0);
    if (ret<0) die("msgrcv");
}

void Produttore(MonitorPC *pc, int id_bambino, int coda_risposte) {
    /*
        TODO: completare inizializzazione lettera e produzione
    */
    Lettera lettera;
    lettera.id_bambino=id_bambino;
    lettera.numero_regali=rand()%5+1;

    produci(pc, lettera);

    /*
        TODO: attesa risposta
    */
    MessaggioRispostaBabbo risposta;
    ReceiveBloc(&risposta, coda_risposte);

    printf("[Produttore %d] Risposta ricevuta: %s\n", getpid(), risposta.messaggio);
}

void Consumatore(MonitorPC *pc, int coda_risposte) {
    int cattivi[] = {3, 5, 7, 9};
    int num_cattivi = sizeof(cattivi) / sizeof(cattivi[0]);

    for (int i=0; i<NUM_BAMBINI; i++) {
        /*
            TODO: completare consumo di una lettera
        */
        Lettera lettera = consuma(pc);

        printf("[Babbo Natale] Ho ricevuto una lettera con ID=%d e regali=%d\n", lettera.id_bambino, lettera.numero_regali);

        /*
            TODO: creazione messaggio di risposta, controllo dell'id e invio del messaggio di risposta
        */
        MessaggioRispostaBabbo risposta;
        
        controlla_buono(&risposta, lettera.id_bambino, cattivi);

        SendSincr(&risposta, coda_risposte);

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

