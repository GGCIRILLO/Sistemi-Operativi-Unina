#include "monitor_signal_continue.h"

#define DIM 5
#define NUM_BAMBINI 10
#define NUM_CATTIVI 4

/*
    TODO: completare le strutture necessarie alla gestione della coda
*/

typedef struct {
/*
    TODO: completare 
*/
} Lettera;

typedef struct {
    Lettera buffer[DIM];
/*
    TODO: completare 
*/
} MonitorPC;

/*
    TODO: completare le strutture per la gestione dello scambio di messaggi con send sincrona
*/

typedef char msg[20];

typedef struct {

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
