#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include "teatro.h"

int main(){

    pid_t pid;
    int status, k;
    
    //Creazione code tra Buyer e Report
    int ds_queue_viewer;

    //create queues
    int key_queue_viewer = ftok(".", 'c'); /* TODO: ottenere chiave per la coda di comunicazione tra viewers e report */
    if (key_queue_viewer<0) die("ftok");

    ds_queue_viewer = msgget(key_queue_viewer, IPC_CREAT|0664); /* TODO: ottenere il descrittore per la coda di comunicazione tra viewers e report */
    if (ds_queue_viewer<0) die("msgget");

    printf("[master] Coda ds_queue_viewer creata! ID: %d\n", ds_queue_viewer);
    
    pid = fork();
    
    if (pid == 0) {                //processo figlio
        /* TODO: lanciare il programma "teatro" in altro eseguibile */
        printf("Avvio teatro\n");
        execl("./teatro", "teatro", NULL);
        perror("Errore teatro");
        exit(-1);
    }
    
    pid = fork();
    
    if (pid == 0) {                //processo figlio
        /* TODO: lanciare il programma "report" in altro eseguibile */
        printf("Avvio processo\n");
        execl("./report", "report", NULL);
        perror("Errore report");
        exit(-1);
        
    }
    
    for (k=0; k<2; k++){
        /* TODO: attendere la terminazione dei processi */
        pid = wait(&status);
        if (pid == -1)
            perror("errore");
        else
            printf ("Figlio n.ro %d e\' morto con status= %d \n ", pid, status);
    }

    msgctl(ds_queue_viewer, IPC_RMID, NULL);
    
    return 0;
}
