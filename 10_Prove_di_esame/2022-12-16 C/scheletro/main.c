#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int key_coda = // TODO
    int id_coda_sensore = //TODO

    if(id_coda_sensore < 0) {
        perror("Errore msgget");
        exit(1);
    }

    pid_t pid;

    pid = fork();

    if(pid == 0) {
        // TODO: processo figlio sensore (eseguibile distinto)    }

    pid = fork();

    if(pid == 0) {
       // TODO: processo figlio smistatore (eseguibile distinto)
       	
    }


    // TODO: attendere completamento dei figli
    
    // TODO: rimuovere la coda
        
    return 0;

}
