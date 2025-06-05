#ifndef HEADER_H
#define HEADER_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_LETTERE 5
#define NUM_BAMBINI 3

/*
    TODO: completare le strutture necessarie per lo scambio di messaggi
*/
#define MESSAGGIO 1

typedef struct {
    long tipo;
    int numero_regali;

} MessaggioRichiesta;

typedef struct {
    long tipo;

} MessaggioRisposta;

typedef struct {
/*
    TODO: completare la struttura per risolvere il problema lettori-scrittori
*/
    int totale_regali;

    int num_lettori;
    int num_scrittori;
    int scrittori_wait;
    int lettori_wait;

    pthread_mutex_t mutex;
    pthread_cond_t cv_lett;
    pthread_cond_t cv_scritt;

} MonitorLettScritt;

static inline void die(const char* x){
    perror(x);
    exit(1);
}

#endif