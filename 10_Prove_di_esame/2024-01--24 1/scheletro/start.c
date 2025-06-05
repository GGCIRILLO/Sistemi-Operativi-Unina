#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header_msg.h"

int main() {

	
    /* TBD: Creare una coppia di code di messaggi UNIX */
    
    
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
    


    /* TBD: Creare 2 processi figli, che eseguano l'eseguibile "client" */
	
	
	/* TBD: Attendere la terminazione dei figli, deallocare le code di messaggi */
    
    return 0;
}
