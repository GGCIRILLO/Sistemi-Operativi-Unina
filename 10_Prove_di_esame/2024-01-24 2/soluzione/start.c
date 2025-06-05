#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header_msg.h"
#include "header_sem.h"


int main() {


    /* TBD: Predisporre le code di messaggi UNIX per la send sincrona */
    int q_mess = queue_create('M');   // messaggio 
    int q_rts  = queue_create('R');   // Ready-To-Send            
    int q_ots  = queue_create('O');   // Ok-To-Send               

    /* TBD: Creare un processo figlio, che esegua l'eseguibile "server" */
    pid_t pid_server = fork();
    if (pid_server<0) die("fork server\n");
    else if (pid_server == 0){
        printf("PID figlio server: %d\n", getpid());
        execl("./server", "./server", NULL);
        die("exec server\n");
    }


    /* TBD: Creare un processo figlio, che esegua l'eseguibile "client" */
    
    pid_t pid_client = fork();
    if (pid_client<0) die("fork client");
    else if (pid_client==0){
        printf("PID figlio client: %d\n", getpid());
        execl("./client", "./client", NULL);
        die("exec client\n");
    }



    /* TBD: Attendere la terminazione dei figli, deallocare le code di messaggi */
    while (wait(NULL)>0);

    msgctl(q_mess, IPC_RMID, NULL);
    msgctl(q_rts, IPC_RMID, NULL);
    msgctl(q_ots, IPC_RMID, NULL);

    return 0;
}