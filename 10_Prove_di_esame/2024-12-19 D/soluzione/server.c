#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "header.h"

int main() {

    /*
        TODO: recupero code e inizializzazione strutture
    */
    int key_req = ftok(".", 'a');
    int key_res = ftok(".", 'b');
    int coda_richieste = msgget(key_req, 0);
    int coda_risposte = msgget(key_res, 0);

    int shm = shmget(IPC_PRIVATE, sizeof(MonitorLettScritt), IPC_CREAT|0664);
    MonitorLettScritt * ls = (MonitorLettScritt*) shmat(shm, NULL, 0);

    inizializza_monitor(ls);

    pid_t pids, pidl;

    srand(time(NULL)*getpid());

    for (int i=0; i<NUM_BAMBINI*NUM_LETTERE; i++) {
        /*
            TODO: creare figli
        */
        pids = fork();
        if (pids==0) {
            Scrittore(coda_richieste, ls);
            exit(0);
        }
        sleep(rand()%3 + 1);

    }

    for (int i=0; i<NUM_BAMBINI*NUM_LETTERE; i++) {
        /*
            TODO: creare figli
        */
        pidl = fork();
        if (pidl==0) {
            Lettore(coda_risposte, ls);
            exit(0);
        }
        sleep(rand()%3 + 1);

    }


    /*
        TODO: attesa terminazione figli
    */
    while(wait(NULL)>0);

    /*
        TODO: distruzione risorse
    */
    distruggi_monitor(ls);
    shmctl(shm, IPC_RMID, NULL);


    return 0;
}