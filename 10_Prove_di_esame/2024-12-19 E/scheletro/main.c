#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "header.h"

int main() {
/*
    TODO: completare la creazione della memoria condivisa e inizializzazione struttura
*/

/*
    TODO: completare la creazione della coda di messaggi
*/
    

/*
    TODO: figlio consumatore
*/

    pid_t pidp;
    for (int i = 0; i < NUM_BAMBINI; i++) {
        /*
            TODO: completare la creazione dei figli produttori
        */
            srand(time(NULL)*getpid());

        sleep(rand() % 3 + 1);
    }

    /*
        TODO: attesa terminazione processi e rimozione strutture
    */

    return 0;
}
