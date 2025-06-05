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

    pid_t pids, pidl;

    for (int i=0; i<NUM_BAMBINI*NUM_LETTERE; i++) {
        /*
            TODO: creare figli
        */
            sleep(rand()%3 + 1);

    }

    for (int i=0; i<NUM_BAMBINI*NUM_LETTERE; i++) {
        /*
            TODO: creare figli
        */
            sleep(rand()%3 + 1);

    }

    /*
        TODO: attesa terminazione figli
    */

    /*
        TODO: distruzione risorse
    */


    return 0;
}