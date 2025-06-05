#include "monitor_signal_continue.h"
#include <stdio.h>
#include <stdlib.h>

#define DIM 5
#define NUM_BAMBINI 10
#define NUM_CATTIVI 4

/*
    TODO: completare le strutture necessarie alla gestione della coda
*/
#define RTS 1
#define OTS 2
#define MESS 3

#define CV_PROD 0
#define CV_CONS 1 

typedef struct {
/*
    TODO: completare 
*/
    int id_bambino;
    int numero_regali;
} Lettera;

typedef struct {
    Lettera buffer[DIM];
/*
    TODO: completare 
*/
    int testa;
    int coda;
    int count;

    Monitor m;
} MonitorPC;

/*
    TODO: completare le strutture per la gestione dello scambio di messaggi con send sincrona
*/

typedef char msg[20];

typedef struct {

    long tipo;

    msg messaggio;
} MessaggioRispostaBabbo;

void inizializza_coda(MonitorPC *m);
void rimuovi_coda(MonitorPC *m);
void produci(MonitorPC *m, Lettera lettera);
Lettera consuma(MonitorPC *m);
void controlla_buono(MessaggioRispostaBabbo * risposta, int id, int *cattivi);

void ReceiveBloc (MessaggioRispostaBabbo *, int);
void SendSincr (MessaggioRispostaBabbo *, int);

void Produttore(MonitorPC *m, int id, int coda_risposte);
void Consumatore(MonitorPC *m, int coda_risposte);

static inline void die(const char * m){
    perror(m);
    exit(1);
}