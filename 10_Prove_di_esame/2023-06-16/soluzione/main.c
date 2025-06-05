#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>

#include "prodcons.h"

void Produttore(MonitorBufferSingolo* b,int id_coda);
void Consumatore(MonitorBufferSingolo* b,int id_coda);

int main() {
	/* TBD: Allocare l'oggetto MonitorBufferSingolo in memoria condivisa */

    int shm_id = shmget(IPC_PRIVATE, sizeof(MonitorBufferSingolo), IPC_CREAT|0664);
    if (shm_id<0) die("shmget");

    MonitorBufferSingolo * b = (MonitorBufferSingolo*) shmat(shm_id, NULL, 0);
    if(b==(void*)-1) die("shmat");
    
    /* TBD: Inizializzare l'oggetto MonitorBufferSingolo */
    init_monitor_buffer_singolo(b);

    
    int id_coda = msgget(IPC_PRIVATE, IPC_CREAT|0664); /* TBD: Allocare una coda di messaggi */
    if (id_coda<0) die("msgget");

	int pid;
    
    /* TBD: Creare un processo figlio, che esegua la funzione "Consumatore()" */
    pid=fork();
    if (pid<0) die("fork consum");
    else if(pid == 0){
        printf("Avvio processo Consumatore pid=%d\n", getpid());
        Consumatore(b, id_coda);
        exit(0);
    }

    /* TBD: Creare un processo figlio, che esegua la funzione "Produttore()" */
    pid = fork();
    if (pid<0) die("fork prod");
    else if  (pid == 0){
        srand(getpid()*time(NULL));
        printf("Avvio processo Produttore pid=%d\n", getpid());
        Produttore(b, id_coda);
        exit(0);
    }
  
    /* TBD: Attendere la terminazione dei processi figli */
    while(wait(NULL)>0);

    /* TBD: Deallocare l'oggetto monitor */
    remove_monitor_buffer_singolo(b);
    shmctl(shm_id, IPC_RMID, NULL);

    /* TBD: Deallocare la coda di messaggi */
    msgctl(id_coda, IPC_RMID, NULL);
}


void Produttore(MonitorBufferSingolo* b,int id_coda) {

    int numero_elementi = rand() % 10;

    printf("[%d][PRODUTTORE] Totale elementi da inviare: %d\n",getpid(),numero_elementi);

    /* TBD: Effettuare una produzione su MonitorBufferSingolo con
            la funzione "produzione_buffer_singolo", inserendo "numero_elementi"
     */
    produzione_buffer_singolo(b, numero_elementi);
    
    for(int i=0; i<numero_elementi; i++) {
    
        sleep(1);

        int val = rand() % 10;

        printf("[%d] [PRODUTTORE] Invio del valore: %d\n", getpid(),val);

		messaggio m;
		m.tipo = MESSAGGIO;
		m.valore = val;
        /* TBD: Inviare il valore "val" tramite la coda di messaggi */
        if (msgsnd(id_coda, (void*)&m, sizeof(m)-sizeof(long), 0)<0) die("msgsnd");

    }
}

void Consumatore(MonitorBufferSingolo* b,int id_coda) {

    /* TBD: Effettuare una consumazione su MonitorBufferSingolo con
            la funzione "consumazione_buffer_singolo", prelevando "numero_elementi"
     */

    int numero_elementi = consumazione_buffer_singolo(b);

    for(int i=0; i<numero_elementi; i++) {

        /* TBD: Ricevere il valore "val" tramite la coda di messaggi */
        messaggio m;
        if (msgrcv(id_coda, (void*)&m, sizeof(m)-sizeof(long), 0, 0)<0) die("msgrcv");

        int val =  m.valore /* TBD */;

        printf("[%d][CONSUMATORE] Ricezione del valore: %d\n", getpid(),val);
    }
}
