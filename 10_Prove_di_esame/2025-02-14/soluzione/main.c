#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "header_msg.h"

int main() {

    key_t chiave_collettore = ftok(".", 'c') /*TODO*/;
    if (chiave_collettore<0) die("ftok");

    int id_queue_collettore = msgget(chiave_collettore, IPC_CREAT|0664) /*TODO*/;
    if (id_queue_collettore<0) die("msgget");

    key_t chiave_server = ftok(".", 's') /*TODO*/;
    if (chiave_server<0) die("ftok");

    int id_queue_server = msgget(chiave_server, IPC_CREAT|0664) /*TODO*/;
    if (id_queue_server<0) die("msgget");

    //TODO: creazione ed eseuzione processo server
    pid_t pid = fork();
    if (pid<0) die("fork");
    else if (pid==0){
        printf("Avvio processo SERVER con pid=%d\n", getpid());
        execl("./server", "server", NULL);
        die("execl");
    }
    

    //TODO: creazione processo collettore
    pid = fork();
    if (pid<0) die("fork");
    else if (pid==0){
        printf("Avvio processo COLLETTORE con pid=%d\n", getpid());
        collettore(id_queue_collettore, id_queue_server);
        exit(0);
    }

    //TODO: creazione processi sensori, ciascuno con il proprio ID
    for (int i=0;i<3;i++){
        pid = fork();
        if (pid<0) die("fork");
        else if (pid==0){
            printf("Avvio processo SENSORE %d con pid=%d\n", i+1, getpid());
            sensore(i+1, id_queue_collettore);
            exit(0);
        }
    }

    //TODO: attesa dei processi figli
    while(wait(NULL)>0);
    printf("[MAIN] processi figli terminati\n");

    //TODO: rimozione risorse IPC
    msgctl(id_queue_collettore, IPC_RMID, NULL);
    msgctl(id_queue_server, IPC_RMID, NULL); // qua o nel server? 
    
    return 0;
}