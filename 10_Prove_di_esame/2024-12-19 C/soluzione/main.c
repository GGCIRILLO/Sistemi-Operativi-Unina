#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "header.h"

int main() {

    /*
        TODO: creazione code di messaggi
    */
    key_t k_req = ftok(".", 'a');
    if (k_req<0) die("ftok");

    key_t k_res = ftok(".", 'b');
    if (k_res<0) die("ftok");

    int coda_richieste = msgget(k_req, IPC_CREAT|0664);

    int coda_risposte = msgget(k_res, IPC_CREAT|0664);

    if (coda_richieste == -1 || coda_risposte == -1) {
        perror("Errore nella creazione delle code di messaggi");
        exit(1);
    }

    /*
        TODO: avvio client e server in eseguibili distinti
    */
    pid_t pid = fork();
    if (pid<0) die("fork");
    else if (pid==0){
        execl("./client", "client", NULL);
        die("execl");
    }

    pid = fork();
    if (pid<0) die("fork");
    else if (pid==0){
        execl("./server", "server", NULL);
        die("execl");
    }

    /*
        TODO: attendo terminazione figli
    */
    while(wait(NULL)>0);

    msgctl(coda_richieste, IPC_RMID, NULL);
    msgctl(coda_risposte, IPC_RMID, NULL);

    return 0;
}
