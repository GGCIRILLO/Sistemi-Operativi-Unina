#ifndef _HEADER_SEM_
#define _HEADER_SEM_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

typedef struct {

    /* TBD: Completare la struttura con le variabili
            necessarie per lo schema lettori-scrittori
     */

} lettscritt;


int Wait_Sem(int id_sem, int numsem);
int Signal_Sem(int id_sem, int numsem);

void scrivi(int id_sem, lettscritt * p, int valore);
int leggi(int id_sem, lettscritt * p);

#endif