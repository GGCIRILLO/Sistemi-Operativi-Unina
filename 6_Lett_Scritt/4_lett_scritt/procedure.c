#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include "header.h"
#include "semafori.h"


void Lettore(int ds_sem, Monitor* m, int id) {
    // TODO: ciclo di 6 letture
    //       - sincronizzazione in stile lettore
    //       - leggere status_code e diagnostic_message
    //       - stampa del valore letto
    //       - sleep(2) per simulare tempo di lettura
    //       - rilascio della sincronizzazione
    for (int i=0; i<6; i++){

        // Inizio lettura 
        Wait_Sem(ds_sem, MUTEXL);

        m->numlettori ++;

        if(m->numlettori == 1) Wait_Sem(ds_sem, SYNCH);

        Signal_Sem(ds_sem, MUTEXL);
        // ---------

        int val = m->status_code;
        char msg[32];
        strncpy(msg, m->diagnostic_message, sizeof(msg));

        printf("[Lettore %d] Stato letto: %d - %s\n", id, val, msg);

        sleep(2);

        // Fine lettura
        Wait_Sem(ds_sem, MUTEXL);

        m->numlettori --;

        if (m->numlettori == 0) Signal_Sem(ds_sem, SYNCH);

        Signal_Sem(ds_sem, MUTEXL);
        // --------
    }
}

void Scrittore(int ds_sem, Monitor* m, int id) {
    // TODO: ciclo di 3 scritture
    //       - generare status_code ∈ [0, 9]
    //       - scegliere messaggio casuale tra {"OK", "FAIL", "WARN", "BOOT"}
    //       - sincronizzazione in stile scrittore (priorità o no)
    //       - scrivere i dati nel monitor
    //       - stampa del valore scritto
    //       - sleep(1) per simulare scrittura
    //       - rilascio della sincronizzazione

    const char* messaggi[] = {"OK", "FAIL", "WARN", "BOOT"};
    srand(getpid() ^ time(NULL)); 

    for (int i = 0; i < 3; i++) {
        int codice = rand() % 10;
        const char* messaggio = messaggi[rand() % 4];

        // Inizio scrittura
        Wait_Sem(ds_sem, MUTEXS);
        m->numscrittori ++;
        if(m->numscrittori == 1) Wait_Sem(ds_sem, SYNCH);
        Signal_Sem(ds_sem, MUTEXS);
        Wait_Sem(ds_sem, MUTEX); 
        // --------

        m->status_code = codice;
        strncpy(m->diagnostic_message, messaggio, sizeof(m->diagnostic_message)-1);
        m->diagnostic_message[31] = '\0';

        printf("[Scrittore %d] Stato aggiornato: %d - %s\n", id, codice, messaggio);
        sleep(1); // Simula scrittura

        // Fine Scrittura
        Signal_Sem(ds_sem, MUTEX);

        Wait_Sem(ds_sem, MUTEXS);

        m->numscrittori --;

        if(m->numscrittori ==0) Signal_Sem(ds_sem, SYNCH);

        Signal_Sem(ds_sem, MUTEXS);
        // ------
    }
}