/****************** MAIN  (p_c_msg.c) ***************************/
#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include "header.h"

int main() {

    int queue;
    pid_t pid;
    int i, status;
    char m[30];

    /* 1) CREAZIONE CODA PRIVATA: visibile solo a questo albero di processi */
    queue = msgget(IPC_PRIVATE, IPC_CREAT | 0664);
    if (queue == -1) { perror("msgget"); exit(1); }

    /* 2) PRIMO fork → PRODUTTORE */
    pid = fork();
    if (pid == 0) {                              /* === FIGLIO PRODUTTORE === */
        printf("Produttore (PID %d)\n", getpid());
        for (i = 0; i < 10; i++) {
            sprintf(m, "stringa %d", i);         /* PREPARA IL TESTO          */
            usleep(100);                         /* PICCOLA ATTESA            */
            Produttore(queue, m);                /* INVIO                    */
        }
        _exit(0);
    }

    /* 3) SECONDO fork → CONSUMATORE */
    pid = fork();
    if (pid == 0) {                              /* === FIGLIO CONSUMATORE === */
        printf("Consumatore (PID %d)\n", getpid());
        sleep(1);                                /* SINCRONIZZAZIONE GREZZA   */
        for (i = 0; i < 10; i++)
            Consumatore(queue);                  /* RICEZIONE & STAMPA        */
        _exit(0);
    }

    /* 4) IL PADRE ATTENDE I 2 FIGLI */
    for (i = 0; i < 2; i++) {
        pid = wait(&status);
        if (pid == -1)
            perror("wait");
        else
            printf("Figlio %d terminato, status=%d\n", pid, status >> 8);
    }

    /* 5) DISTRUZIONE CODA MSG */
    msgctl(queue, IPC_RMID, NULL);
    return 0;
}
/***************************************************************/