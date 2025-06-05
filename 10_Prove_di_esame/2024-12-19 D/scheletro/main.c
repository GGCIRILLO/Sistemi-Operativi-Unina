#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "header.h"

int main() {
    /*
        TODO: creazione code di messaggi 
    */
    if (coda_richieste == -1 || coda_risposte == -1) {
        perror("Errore nella creazione delle code");
        exit(1);
    }

    /*
        TODO: avvio del client e server in eseguibili distinti
    */

    /*
        TODO: attendere terminazione processi
    */

    msgctl(coda_richieste, IPC_RMID, NULL);
    msgctl(coda_risposte, IPC_RMID, NULL);

    return 0;
}