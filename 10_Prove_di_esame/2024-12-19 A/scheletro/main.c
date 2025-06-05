#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "header.h"

#define NUM_CONSUMI 10

int main() {

    /*
        TODO: inizializzazione segmenti di memoria e strutture condivisi
    */

    pid_t pid_p, pid_c1, pid_c2, pid_b;

    /*
        TODO: creazione di 4 figli: un Produttore, un Consumatore1, un Consumatore2 e BabboNatale
    */

    /*
        TODO: attesa terminazione figli
    */

    /*
        TODO: distruzione strutture
    */

    return 0;
}