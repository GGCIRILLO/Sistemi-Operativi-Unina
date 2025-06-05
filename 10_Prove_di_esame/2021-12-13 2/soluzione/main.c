#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#include "header.h"

int main() {

    int shm_id = shmget(IPC_PRIVATE, sizeof(MonitorCoda),IPC_CREAT|0664); /* TBD: Ottenere un descrittore della shared memory */
    
    if (shm_id < 0)
    {
        perror("Errore creazione shared memory");
        exit(1);
    }
    
    MonitorCoda *p = (MonitorCoda*) shmat(shm_id, NULL, 0); /* TBD: Effettuare l'attache della shared memory */
    
    if (p == (void *)-1)
    {
        perror("Errore attach shared memory");
        exit(1);
    }

    /* TBD: Inizializzare monitor e variabili per la sincronizzazione tramite la procedura inizializza(...) */
    inizializza(p);
    
    /* TBD: Aggiungere codice per la creazione dei processi produttori e consumatori */
    for(int i=0;i<NUM_PRODUTTORI;i++){
        pid_t pid = fork();
        if (pid==0){
            printf("Avvio processo produttore\n");
            produttore(p);
            exit(0);
        }
    }

    for(int i=0;i<NUM_CONSUMATORI;i++){
        pid_t pid = fork();
        if (pid==0){
            printf("avvio processo consumatore\n");
            consumatore(p);
            exit(0);
        }
    }

    /* TBD: Aggiungere codice per l'attesa della terminazione dei processi produttori e consumatori */
    while(wait(NULL)>0);

    /* TBD: Aggiungere codice per la rimozione del monitor tramite la procedura rimuovi(...) */
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}

