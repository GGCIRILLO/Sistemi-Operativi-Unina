#ifndef _HEADER_SEM_
#define _HEADER_SEM_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <stdio.h>
#include "header_msg.h"

#define SYNCH   0   /* esclusione scrittore / primo-ultimo lettore */
#define MUTEXL  1   /* protezione di num_lettori                   */
#define NSEM    2

typedef struct {

    /* TBD: Completare la struttura con le variabili
            necessarie per lo schema lettori-scrittori
     */
    int num_lettori;
    int buffer;

} lettscritt;


int Wait_Sem(int id_sem, int numsem);
int Signal_Sem(int id_sem, int numsem);

void scrivi(int id_sem, lettscritt * p, int valore);
int leggi(int id_sem, lettscritt * p);

// per comodità ho creato una funzione per gestire gli errori
static inline void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// e una per accedere alle code
static inline int queue_create(char proj_id)
{
    key_t k = ftok(".", proj_id);
    if (k == -1) die("ftok");

    int q = msgget(k, IPC_CREAT | 0666);
    if (q == -1) die("msgget");

    return q;
}

#endif