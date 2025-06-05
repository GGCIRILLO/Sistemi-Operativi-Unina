#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header_msg.h"

int main() {

	
    /* TBD: Creare una coppia di code di messaggi UNIX */
    key_t key_send = ftok(".", 'S');
    key_t key_rcv = ftok(".", 'R');
    
    int send_queue=msgget(key_send, IPC_CREAT| 0664);
    int rcv_queue=msgget(key_rcv, IPC_CREAT | 0664);
    
    
    if(send_queue<0){
    	perror("Errore nella creazione della coda sender\n");
    	exit(1);
    }
	
	if(rcv_queue<0){
    	perror("Errore nella creazione della coda receiver\n");
    	exit(1);
    }
	

    /* TBD: Creare un processo figlio, che esegua l'eseguibile "server" */
    pid_t pid = fork();
    if (pid<0){
        perror("Errore fork");
        exit(1);
    } else if (pid==0){
        printf("Creazione processo server\n");
        execl("./server", "./server", NULL );
        perror("Tornato dall'exec ... errore\n");
        exit(1);
    }
    


    /* TBD: Creare 2 processi figli, che eseguano l'eseguibile "client" */
    for (int i=0;i<2;i++){
        pid_t pid2 = fork();
        if (pid2<0){
            perror("Errore fork");
            exit(1);
        } else if (pid2==0){
            printf("Creazione processo client %d\n", i);
            execl("./client", "./client", NULL);
            perror("Tornato dall'exec ... errore\n");
            exit(1);
        }
    }
	
	
	/* TBD: Attendere la terminazione dei figli, deallocare le code di messaggi */
    for (int i=0;i<4;i++) wait(NULL);

    msgctl(send_queue, IPC_RMID, 0);
    msgctl(rcv_queue, IPC_RMID, 0);
    
    return 0;
}
