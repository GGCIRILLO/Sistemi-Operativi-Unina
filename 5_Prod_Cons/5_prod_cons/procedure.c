#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include "procedure.h"
#include "semafori.h"

void studente(coda_stampa *coda, int semid) {
    printf("Avvio Figlio studente PID=%d\n", getpid());

    // TODO: Attendere spazio disponibile (SPAZIO_DISPONIBILE)
    Wait_Sem(semid, SPAZIO_DISPONIBILE);

    // TODO: Entrare in sezione critica (MUTEX_STUDENTI)
    Wait_Sem(semid, MUTEX_STUDENTI);

    // TODO: Inserire documento in buffer
    int r = rand()%10000 + 1000;
    coda->buffer[coda->testa] = r;

    printf("Aggiornato Buffer a %d con %d\n", coda->testa, coda->buffer[coda->testa]);

    // TODO: Aggiornare indice testa
    coda->testa = (coda->testa + 1) % DIM_BUFFER;

    // TODO: Aggiorna studenti rimasti
    coda->studenti_vivi--;

    // TODO: Uscire da sezione critica (MUTEX_STUDENTI)
    Signal_Sem(semid, MUTEX_STUDENTI);

    // TODO: Segnalare presenza di nuovo documento (MESSAGGIO_DISPONIBILE)
    Signal_Sem(semid, MESSAGGIO_DISPONIBILE);

    // TODO: Terminare
    exit(0);
}

void addetto(coda_stampa *coda, int semid) {

    printf("Avvio Addetto PID=%d\n", getpid());

    while(1){

        if (coda->studenti_vivi==0) break;
        // TODO: Attendere presenza documento (MESSAGGIO_DISPONIBILE)
        Wait_Sem(semid, MESSAGGIO_DISPONIBILE);

        // TODO: Entrare in sezione critica (MUTEX_ADDETTI)
        Wait_Sem(semid, MUTEX_ADDETTI);

        // TODO: Prelevare documento dal buffer
        int arch = coda->buffer[coda->coda];
        // TODO: Aggiornare indice coda
        coda->coda = (coda->coda+1)%DIM_BUFFER;

        // TODO: Uscire da sezione critica (MUTEX_ADDETTI)
        Signal_Sem(semid, MUTEX_ADDETTI);

        // TODO: Segnalare spazio disponibile (SPAZIO_DISPONIBILE)
        Signal_Sem(semid, SPAZIO_DISPONIBILE);

        // TODO: Simulare archiviazione documento
        sleep(1);

        printf("Documento archiviato %d\n", arch);
    }

    // TODO: Terminare
    exit(0);
}