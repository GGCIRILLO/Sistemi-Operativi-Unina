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
    int key_req = ftok(".", 'a');
    int key_res = ftok(".", 'b');
    int coda_richieste = msgget(key_req, IPC_CREAT|0664);
    int coda_risposte = msgget(key_res, IPC_CREAT|0664);

    if (coda_richieste == -1 || coda_risposte == -1) {
        perror("Errore nella creazione delle code");
        exit(1);
    }

    /*
        TODO: avvio del client e server in eseguibili distinti
    */
    pid_t pid = fork();
    if (pid == 0) {
        execl("./client", "client", NULL);
        perror("execl client");
        exit(1);
    }

    pid = fork();
    if (pid == 0) {
        execl("./server", "server", NULL);
        perror("execl server");
        exit(1);
    }

    while(wait(NULL)>0);


    msgctl(coda_richieste, IPC_RMID, NULL);
    msgctl(coda_risposte, IPC_RMID, NULL);

    return 0;
}