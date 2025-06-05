#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "header_msg.h"
#include "header_prodcons.h"


int main() {

    /* TBD: Creare le code di messaggi per la send sincrona*/
    key_t k_mess = ftok(".", 'm');
    if (k_mess<0) die("ftok");

    key_t k_rts = ftok(".", 'r');
    if (k_rts<0) die("ftok");

    key_t k_ots = ftok(".", 'o');
    if (k_ots<0) die("ftok");

    int coda_mess = msgget(k_mess, IPC_CREAT|0664);
    if (coda_mess<0) die("msgget");

    int coda_rts = msgget(k_rts, IPC_CREAT|0664);
    if (coda_rts<0) die("msgget");

    int coda_ots = msgget(k_ots, IPC_CREAT|0664);
    if (coda_ots<0) die("msgget");

    /* TBD: Creare un processo figlio, ed eseguire il programma "server" */
    pid_t pid = fork();
    if (pid<0) die("fork");
    else if (pid==0){
        execl("./server", "server", NULL);
        die("execl");
    }
    printf("[START] Processo server avviato\n");

    /* TBD: Creare un processo figlio, ed eseguire il programma "client" */
    pid = fork();
    if (pid<0) die("fork");
    else if (pid==0){
        execl("./client", "client", NULL);
    }
    printf("[START] Processo client avviato\n");


    /* TBD: Attendere la terminazione dei processi figli */
    while(wait(NULL)>0);

    /* TBD: Eliminare le code di messaggi */
    msgctl(coda_mess, IPC_RMID, NULL);
    msgctl(coda_rts, IPC_RMID, NULL);
    msgctl(coda_ots, IPC_RMID, NULL);

    return 0;
}