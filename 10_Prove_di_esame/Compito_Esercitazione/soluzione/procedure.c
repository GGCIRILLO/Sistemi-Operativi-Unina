#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons * p) {

   // inizializza struttura coda circolare

    p->testa=0;
    p->coda=0;

    init_monitor(&p->m, NUM_CV);
}

void produci(VettoreProdCons * p, int valore) {

    // produzione con meccanismo di coda circolare
    enter_monitor(&p->m);

    if (((p->testa + 1) % DIM) == p->coda){ 
        printf("[MAIN PRODUTTORE %d] Sospeso\n", getpid());
        wait_condition(&p->m, VARCOND_P);
        printf("[MAIN PRODUTTORE %d] Ripreso\n", getpid());
    }
    p->buff[p->testa] = valore;
    p->testa = (p->testa +1 ) %DIM;

    signal_condition(&p->m, VARCOND_C);
    leave_monitor(&p->m);
}

int consuma(VettoreProdCons * p) {

    // consumo con meccanismo di coda circolare
    enter_monitor(&p->m);

    if (p->testa == p->coda){
        printf("[MAIN CONSUMATORE %d] Sospeso\n", getpid());
        wait_condition(&p->m, VARCOND_C);
        printf("[MAIN CONSUMATORE %d] Ripreso\n", getpid());
    }

    int val = p->buff[p->coda];
    
    p->coda = (p->coda +1 ) % DIM;

    signal_condition(&p->m, VARCOND_P);

    leave_monitor(&p->m);

    return val;

}

void rimuovi_vettore(VettoreProdCons * p) {

    // 
    remove_monitor(&p->m);    
}


void inizializza_buffer(BufferMutuaEsclusione * p) {

   // inizializzazione semaforo per aggiornare il buffer in mutua esclusione
   p->sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0664);
   if (p->sem_id<0) die("semget buff");

   if (semctl(p->sem_id, MUTEX, SETVAL, 1)<0) die("semctl buff");

   p->val = 0;

}

void aggiorna(BufferMutuaEsclusione * p, int valore) {

    // aggiorno valore in mutua esclusione
    Wait_Sem(p->sem_id, MUTEX);

    p->val += valore;

    printf("[MAIN CONSUMATORE %d] Aggiorno buffer: %d\n", getpid(), p->val);

    Signal_Sem(p->sem_id, MUTEX);
}

void rimuovi_buffer(BufferMutuaEsclusione * p) {

    //
    if (semctl(p->sem_id, 0, IPC_RMID)<0) die("semctl remove");
}


