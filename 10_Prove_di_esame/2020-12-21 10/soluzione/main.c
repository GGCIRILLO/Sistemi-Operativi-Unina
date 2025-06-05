#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include "header.h"
#include "store.h"

#define NUM_VIEWERS 3
#define NUM_UPDATERS 2


int main(){

    pid_t pid;
    int status, k;
    
    //Creazione code richieste e risposte
    int ds_queue_request, ds_queue_response;

    //create queues
    int key_queue_request = ftok(".", 'A'); // TODO aggiungere codice per la generazione della chiave
    int key_queue_response = ftok(".", 'B'); // TODO aggiungere codice per la generazione della chiave
    if (key_queue_request <0 || key_queue_response<0 ) die("ftok main");

    // TODO aggiungere codice di inizializzazione delle code
    ds_queue_request = msgget(key_queue_request, IPC_CREAT|0664); //...
    ds_queue_response = msgget(key_queue_response, IPC_CREAT|0664); //...
    if (ds_queue_request<0 || ds_queue_response<0 ) die("msgget main");
    
    printf("[master] Coda ds_queue_request creata! ID: %d\n", ds_queue_request);
    printf("[master] Coda ds_queue_response creata! ID: %d\n", ds_queue_response);
    
    // TODO aggiungere codice per generare NUM_VIEWERS processi viewers, attraverso l'exec
    for (int i=0;i<NUM_VIEWERS;i++){
        pid = fork();
        sleep(1);
        if (pid<0) die("fork Viewers");
        else if (pid==0){
            printf("Avvio processo Viewer pid=%d\n", getpid());
            execl("./viewer", "viewer", NULL);
            die("execl viewer");
        }
    }
    

    // TODO aggiungere codice per generare NUM_UPDATERS processi updaters, attraverso l'exec
    for (int i=0;i<NUM_UPDATERS;i++){
        pid = fork();
        sleep(1);
        if (pid<0) die("fork Updater");
        else if (pid==0){
            printf("Avvio processo Updater pid=%d\n", getpid());
            execl("./updater", "updater", NULL);
            die("execl updater");
        }
    }
    

    // TODO aggiungere codice per generare 1 processo store, attraverso l'exec
    pid=fork();
    if(pid<0) die("fork store");
    else if(pid==0){
        printf("Avvio processo Store pid=%d\n", getpid());
        execl("./store", "store", NULL);
        die("execl store");
    }
    
    for (k=0; k<NUM_VIEWERS+NUM_UPDATERS+1; k++){
        pid = wait(&status);
        if (pid == -1)
            perror("errore");
        else
            printf ("[master] Figlio n.ro %d e\' morto con status= %d \n", pid, status);
    }

    // TODO aggiungere codice per la rimozione delle code
    msgctl(ds_queue_request, IPC_RMID, NULL);
    msgctl(ds_queue_response, IPC_RMID, NULL);

    printf("[master] code rimosse\n");
    
    return 0;
}
