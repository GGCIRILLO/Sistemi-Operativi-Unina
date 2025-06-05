#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "prodcons.h"

void Produttore(MonitorVettoreCircolare *p, MonitorBufferSingolo *b);
void Consumatore(MonitorVettoreCircolare *p, MonitorBufferSingolo *b);

int main() {

    int shm1 = shmget(IPC_PRIVATE, sizeof(MonitorVettoreCircolare), IPC_CREAT|0664);
    if (shm1<0) die("shmget");

    MonitorVettoreCircolare * p = (MonitorVettoreCircolare*) shmat(shm1, NULL, 0) /* TBD: Allocare l'oggetto MonitorVettoreCircolare in memoria condivisa */;
    if (p==(void*)-1) die("shmat");
    init_monitor_circolare(p);


    int shm2 = shmget(IPC_PRIVATE, sizeof(MonitorBufferSingolo), IPC_CREAT|0664);
    if (shm2<0) die("shmget");

    MonitorBufferSingolo * b = (MonitorBufferSingolo*) shmat(shm2, NULL, 0) /* TBD: Allocare l'oggetto MonitorBufferSingolo in memoria condivisa */;
    if (b==(void*)-1) die("shmat");

    init_monitor_buffer_singolo(b);

    /* TBD: Creare un processo figlio, che esegua la funzione "Produttore()" */
    pid_t pid = fork();
    if (pid<0) die("fork");
    else if(pid==0){
        Produttore(p, b);
        exit(0);
    }

    /* TBD: Creare un processo figlio, che esegua la funzione "Consumatore()" */
    pid = fork();
    if (pid<0) die("fork");
    else if(pid==0){
        Consumatore(p, b);
        exit(0);
    }


    /* TBD: Attenere la terminazione dei processi figli */
    while(wait(NULL)>0);

    remove_monitor_circolare(p);
    remove_monitor_buffer_singolo(b);

    /* TBD: Deallocare gli oggetti monitor */
    shmctl(shm1, IPC_RMID, NULL);
    shmctl(shm2, IPC_RMID, NULL);

    return 0;
}


void Produttore(MonitorVettoreCircolare *p, MonitorBufferSingolo *b) {

    srand(time(NULL)^getpid());

    int numero_elementi = rand() % 10;

    printf("[PRODUTTORE] Totale elementi da produrre: %d\n", numero_elementi);

    /* TBD: Effettuare una produzione su MonitorBufferSingolo con
            la funzione "produzione_buffer_singolo", inserendo "numero_elementi"
     */
    produzione_buffer_singolo(b, numero_elementi);


    for(int i=0; i<numero_elementi; i++) {
    
        sleep(1);

        int val = rand() % 10;

        printf("[PRODUTTORE] Prodotto: %d\n", val);

        /* TBD: Chiamare la funzione "produzione_circolare" per produrre
                il valore "val"
         */
        produzione_circolare(p, val);
    }
}

void Consumatore(MonitorVettoreCircolare *p, MonitorBufferSingolo *b) {

    /* TBD: Effettuare una consumazione su MonitorBufferSingolo con
            la funzione "consumazione_buffer_singolo", prelevando "numero_elementi"
     */

    int numero_elementi = consumazione_buffer_singolo(b); /* TBD */

    printf("[CONSUMATORE] Totale elementi da consumare: %d\n", numero_elementi);


    for(int i=0; i<numero_elementi; i++) {

        /* TBD: Chiamare la funzione "consumazione_circolare" per prelevare
                un valore e copiarlo in "val"
         */
        

        int val = consumazione_circolare(p); /* TBD */

        printf("[CONSUMATORE] Consumato: %d\n", val);
    }
}
