#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "header.h"

int main() {

    /*
        TODO: creazione code di messaggi
    */

    if (coda_richieste == -1 || coda_risposte == -1) {
        perror("Errore nella creazione delle code di messaggi");
        exit(1);
    }

    /*
        TODO: avvio client e server in eseguibili distinti
    */

    /*
        TODO: attendo terminazione figli
    */

    msgctl(coda_richieste, IPC_RMID, NULL);
    msgctl(coda_risposte, IPC_RMID, NULL);

    return 0;
}
