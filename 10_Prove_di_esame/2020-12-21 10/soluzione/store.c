#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include "store.h"

#define NUM_LETTORI 3
#define NUM_SCRITTORI 2

// code di richiesta e risposte
int ds_queue_request, ds_queue_response;

int main(){
    pid_t pid;
    int status, k;

    Magazzino* magazzino;
    
    // Creazione code
    int key_queue_request = ftok(".", 'A'); // TODO aggiungere codice per la generazione della chiave
    int key_queue_response = ftok(".", 'B'); // TODO aggiungere codice per la generazione della chiave
    if (key_queue_request <0 || key_queue_response<0 ) die("ftok store");

    // TODO aggiungere codice di inizializzazione delle code
    ds_queue_request = msgget(key_queue_request, 0); //...
    ds_queue_response = msgget(key_queue_response, 0); //...
    if (ds_queue_request<0 || ds_queue_response<0 ) die("msgget store");

    printf("[store] Coda ds_queue_request ID: %d\n", ds_queue_request);
    printf("[store] Coda ds_queue_response ID: %d\n", ds_queue_response);

    // Creazione shared memory del magazzino
    int ds_shm_magazzino;
    int key_shm_magazzino = IPC_PRIVATE;// TODO aggiungere chiave

    // TODO aggiungere codice per la creazine e l'attach della shared memory
    ds_shm_magazzino = shmget(key_shm_magazzino, sizeof(Magazzino), IPC_CREAT|0664); // ... get
    if (ds_shm_magazzino<0) die("shmget");

    magazzino = (Magazzino*) shmat(ds_shm_magazzino, NULL, 0); //... attach
    if (magazzino==(void*)-1) die("shmat");

    init_magazzino(magazzino);

    // creazione processi
    for (k = 0; k < NUM_LETTORI; k++) {
        pid = fork();
        if (pid == 0) {                //processo figlio
            lettore(magazzino);
            exit(0); 
        }
    }

     for (k = 0; k < NUM_SCRITTORI; k++) {
        pid = fork();
        if (pid == 0) {                //processo figlio
            scrittore(magazzino);
            exit(0); 
        }
    }

    for (k=0; k<NUM_LETTORI+NUM_SCRITTORI; k++){
        pid = wait(&status);
        if (pid == -1)
            perror("errore");
        else
            printf ("[store] Figlio n.ro %d e\' morto con status= %d \n", pid, status);
    }

    destroy_magazzino(magazzino);
    // TODO aggiungere codice per la rimozione della shared memory
    shmctl(ds_shm_magazzino, IPC_RMID, NULL);
    return 0;

}
