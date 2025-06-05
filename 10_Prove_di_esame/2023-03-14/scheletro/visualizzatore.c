#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "header.h"

void printer(int coda, long v) {

    int i;
    for (i = 0; i < NUM_LETTORI*NUM_OPERAZIONI/2; i++){
        msg mess;
        //TODO: ricezione del messaggio per il volo: "v"
        printf("Il volo %ld ha cambiato gate; nuovo gate: %d\n",v,mess.gate);
    }
}

int main() {


    //TODO: creazione coda
    key_t c_coda = /***/;
    // ..

    //TODO: creazione 2 processi visualizzatori, uno per volo 1 e uno per volo 2
    pid_t pid;
    int i;
    for (i=0;i<2;i++){
       //...
    }

    for(i=0;i<2;i++)
        wait(NULL);

    //TODO: rimozione coda
    
    return 0;
}