#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"


void produttore(struct prodcons * p, int ds_sem) {

    int i = 0;

    // TODO: Wait su SPAZIO_DISPONIBILE per assicurarsi che ci sia spazio libero
    Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);

    // TODO: Wait su MUTEX_P per entrare in sezione critica (accesso vettore stato)
    Wait_Sem(ds_sem, MUTEX_P);

    // TODO: Cercare un buffer libero (BUFFER_VUOTO) nel vettore stato[]
    while(i<DIM_BUFFER && p->stato[i]!=BUFFER_VUOTO) i++;

    // TODO: Marcare il buffer trovato come BUFFER_INUSO
    if (i<DIM_BUFFER){
        p->stato[i]=BUFFER_INUSO;
    }

    // TODO: Signal su MUTEX_P per uscire dalla sezione critica
    Signal_Sem(ds_sem, MUTEX_P);

    // TODO: Simulare il tempo di produzione (sleep)
    sleep(2);

    // TODO: Generare un valore casuale e scriverlo nel buffer trovato
    int n = rand()%100;
    p->buffer[i]=n;
    printf("Valore prodotto:%d\n", n);

    // TODO: Marcare il buffer come BUFFER_PIENO
    p->stato[i]=BUFFER_PIENO;


    // TODO: Signal su MESSAGGIO_DISPONIBILE per segnalare messaggio disponibile
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore(struct prodcons * p, int ds_sem) {

    int i = 0;

    // TODO: Wait su MESSAGGIO_DISPONIBILE per assicurarsi che ci sia qualcosa da consumare
    Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);

    // TODO: Wait su MUTEX_C per entrare in sezione critica (accesso vettore stato)
    Wait_Sem(ds_sem, MUTEX_C);

    // TODO: Cercare un buffer pieno (BUFFER_PIENO) nel vettore stato[]
    while (i<DIM_BUFFER && p->stato[i]!=BUFFER_PIENO) i++;

    // TODO: Marcare il buffer trovato come BUFFER_INUSO
    if(i<DIM_BUFFER) p->stato[i]=BUFFER_INUSO;

    // TODO: Signal su MUTEX_C per uscire dalla sezione critica
    Signal_Sem(ds_sem, MUTEX_C);

    // TODO: Simulare il tempo di consumo (sleep)
    sleep(2);

    // TODO: Leggere il valore dal buffer trovato e stamparlo
    printf("Consumo valore : %d\n", p->buffer[i]);

    // TODO: Marcare il buffer come BUFFER_VUOTO
    p->stato[i]=BUFFER_VUOTO;

    // TODO: Signal su SPAZIO_DISPONIBILE per segnalare spazio disponibile
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
}