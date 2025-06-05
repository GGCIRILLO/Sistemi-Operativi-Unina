#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#include "header.h"

int main() {

    int shm_id = /* TBD: Ottenere un descrittore della shared memory */
    
    if (shm_id < 0)
    {
        perror("Errore creazione shared memory");
        exit(1);
    }
    
    MonitorCoda *p = /* TBD: Effettuare l'attache della shared memory */
    
    if (p == (void *)-1)
    {
        perror("Errore attach shared memory");
        exit(1);
    }

    /* TBD: Inizializzare monitor e variabili per la sincronizzazione tramite la procedura inizializza(...) */
    
    /* TBD: Aggiungere codice per la creazione dei processi produttori e consumatori */

    /* TBD: Aggiungere codice per l'attesa della terminazione dei processi produttori e consumatori */
    
    /* TBD: Aggiungere codice per la rimozione del monitor tramite la procedura rimuovi(...) */
    
    return 0;
}

