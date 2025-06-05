#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int key_coda = ftok(FTOK_PATH, FTOK_CHAR);// TODO
    if (key_coda<0) die("ftok");

    int id_coda_sensore = msgget(key_coda, IPC_CREAT|0664); //TODO
    if(id_coda_sensore < 0) {
        perror("Errore msgget");
        exit(1);
    }

    pid_t pid;

    pid = fork();
    if (pid<0) die("fork");

    if(pid == 0) {
        // TODO: processo figlio sensore (eseguibile distinto)    
        execl("./sensore", "sensore", NULL);
        die("execl");
    }

    pid = fork();

    if(pid == 0) {
       // TODO: processo figlio smistatore (eseguibile distinto)
       execl("./smistatore", "smistatore", NULL);
       die("execl");
    }


    // TODO: attendere completamento dei figli
    while(wait(NULL)>0);
    
    // TODO: rimuovere la coda
    msgctl(id_coda_sensore, IPC_RMID, NULL);
        
    return 0;

}
