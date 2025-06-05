#ifndef HEADER_H
#define HEADER_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define NUM_LETTERE 5
#define NUM_BAMBINI 3

/*
    TODO: completare le strutture necessarie per lo scambio di messaggi
*/

typedef struct {

} MessaggioRichiesta;

typedef struct {

} MessaggioRisposta;

typedef struct {
/*
    TODO: completare la struttura per risolvere il problema lettori-scrittori
*/
} MonitorLettScritt;

#endif