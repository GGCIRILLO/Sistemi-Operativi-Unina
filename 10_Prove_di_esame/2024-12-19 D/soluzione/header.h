#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "monitor_signal_continue.h"

#define NUM_BAMBINI 3
#define NUM_LETTERE 5

/*
    TODO: completare le strutture necessarie allo scambio di messaggi e alla risoluzione del problema lett-scritt con monitor
*/
#define CV_SCR 0
#define CV_LET 1


typedef struct {
    long tipo;
    int numero_regali;

} MessaggioRichiesta;

typedef struct {

    long tipo;

} MessaggioRisposta;

typedef struct {

    int totale_regali;

    int num_lettori;
    int num_scrittori;

    Monitor m;

} MonitorLettScritt;

// Funzioni per il monitor lettori-scrittori
void inizializza_monitor(MonitorLettScritt *ls);
void distruggi_monitor(MonitorLettScritt *ls);
void inizio_lettura(MonitorLettScritt *ls);
void fine_lettura(MonitorLettScritt *ls);
void inizio_scrittura(MonitorLettScritt *ls);
void fine_scrittura(MonitorLettScritt *ls);

void Scrittore(int codareq, MonitorLettScritt *ls);
void Lettore(int codaresp, MonitorLettScritt *ls);

#endif