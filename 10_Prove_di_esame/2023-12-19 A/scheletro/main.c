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
    int key_queue_viewer = /* TODO: ottenere chiave per la coda di comunicazione tra viewers e report */
    
    ds_queue_viewer = /* TODO: ottenere il descrittore per la coda di comunicazione tra viewers e report */
    
    printf("[master] Coda ds_queue_viewer creata! ID: %d\n", ds_queue_viewer);
    
    pid = fork();
    
    if (pid == 0) {                //processo figlio
        /* TODO: lanciare il programma "teatro" in altro eseguibile */
        perror("Errore teatro");
        exit(-1);
    }
    
    pid = fork();
    
    if (pid == 0) {                //processo figlio
        /* TODO: lanciare il programma "report" in altro eseguibile */
        perror("Errore report");
        exit(-1);
        
    }
    
    for (k=0; k<2; k++){
        /* TODO: attendere la terminazione dei processi */
        if (pid == -1)
            perror("errore");
        else
            printf ("Figlio n.ro %d e\' morto con status= %d \n ", pid, status);
    }
    
    return 0;
}
