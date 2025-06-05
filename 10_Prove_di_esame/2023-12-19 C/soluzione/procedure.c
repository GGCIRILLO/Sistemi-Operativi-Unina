#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons * p) {

    /* TBD: Inizializzare la struttura dati "VettoreProdCons" */
    p->num_liberi=0;
    p->num_occupati=0;
    for (int i=0;i<DIM;i++){
        p->stato[i]=LIBERO;
    }

    init_monitor(&p->m, 2);
}

void produci(VettoreProdCons * p, int valore) {

    /* TBD: Implementare la sincronizzazione, mediante
     *      l'algoritmo del vettore di stato
     */
    
    enter_monitor(&p->m);

    if (p->num_occupati==DIM){
        wait_condition(&p->m, CV_PROD);
    }

    int i=0;
    while(i<DIM && p->stato[i]!=LIBERO) i++;

    p->num_liberi--;
    p->stato[i]=IN_USO;

    leave_monitor(&p->m);

    p->buffer[i] = valore;

    enter_monitor(&p->m);

    p->stato[i]=OCCUPATO;
    p->num_occupati++;

    signal_condition(&p->m, CV_CONS);

    leave_monitor(&p->m);    
}

int consuma(VettoreProdCons * p) {

    int valore;

    /* TBD: Implementare la sincronizzazione, mediante
     *      l'algoritmo del vettore di stato
     */
    enter_monitor(&p->m);

    if (p->num_occupati==0){
        wait_condition(&p->m, CV_CONS);
    }

    int i=0;
    while(i<DIM && p->stato[i]!=OCCUPATO)i++;

    p->stato[i]=IN_USO;
    p->num_occupati--;

    leave_monitor(&p->m);

    valore = p->buffer[i];

    enter_monitor(&p->m);

    p->num_liberi++;
    p->stato[i]=LIBERO;

    signal_condition(&p->m, CV_PROD);

    leave_monitor(&p->m);

    return valore;

}

void rimuovi_vettore(VettoreProdCons * p) {

    /* TBD: De-inizializzare la struttura dati "VettoreProdCons" */
    remove_monitor(&p->m);
}


void inizializza_buffer(BufferMutuaEsclusione * p) {

    /* TBD: Inizializzare la struttura dati "BufferMutuaEsclusione" */
    p->buffer = 0;

    p->sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0664);

    semctl(p->sem_id, MUTEX, SETVAL, 1);
}

void aggiorna(BufferMutuaEsclusione * p, int valore) {

    /* TBD: Aggiungere la sincronizzazione per la mutua esclusione */
    Wait_Sem(p->sem_id, MUTEX);

    p->buffer += valore;

    printf("[AGGIORNA] Nuovo valore del buffer: %d\n", p->buffer);

    Signal_Sem(p->sem_id, MUTEX);
}

void rimuovi_buffer(BufferMutuaEsclusione * p) {

    /* TBD: De-inizializzare la struttura dati "BufferMutuaEsclusione" */
    semctl(p->sem_id, 0, IPC_RMID);
}


