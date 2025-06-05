#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include "header.h"

int main() {
/*
    TODO: completare la creazione della memoria condivisa e inizializzazione struttura
*/
    int shm = shmget(IPC_PRIVATE, sizeof(MonitorPC), IPC_CREAT|0664);
    if (shm<0) die("shmget");

    MonitorPC* m = (MonitorPC*) shmat(shm, NULL, 0);
    if (m==(void*)-1) die("shmat");

    inizializza_coda(m);
/*
    TODO: completare la creazione della coda di messaggi
*/
    int coda = msgget(IPC_PRIVATE, IPC_CREAT|0664);
    if (coda<0) die("msgget");
    

/*
    TODO: figlio consumatore
*/
    pid_t pid = fork();
    if (pid<0) die("fork");
    else if(pid==0){
        Consumatore(m, coda);
        exit(0);
    }

    pid_t pidp;
    for (int i = 0; i < NUM_BAMBINI; i++) {
        /*
            TODO: completare la creazione dei figli produttori
        */
        srand(time(NULL)*getpid());
        pidp=fork();
        if (pidp==0){
            int id = rand()%11;
            Produttore(m, id, coda);
            exit(0);
        } else if(pidp==0) die("fork");

        sleep(rand() % 3 + 1);
    }

    /*
        TODO: attesa terminazione processi e rimozione strutture
    */
    while(wait(NULL)>0);

    shmctl(shm, IPC_RMID, NULL);

    msgctl(coda, 0, IPC_RMID);

    return 0;
}
