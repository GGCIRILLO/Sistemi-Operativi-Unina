#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "prodcons.h"

void Produttore(MonitorVettoreCircolare *p, MonitorBufferSingolo *b);
void Consumatore(MonitorVettoreCircolare *p, MonitorBufferSingolo *b);

int main() {


    MonitorVettoreCircolare * p = /* TBD: Allocare l'oggetto MonitorVettoreCircolare in memoria condivisa */;

    init_monitor_circolare(p);



 
    MonitorBufferSingolo * b = /* TBD: Allocare l'oggetto MonitorBufferSingolo in memoria condivisa */;

    init_monitor_buffer_singolo(b);


    /* TBD: Creare un processo figlio, che esegua la funzione "Produttore()" */


    /* TBD: Creare un processo figlio, che esegua la funzione "Consumatore()" */


    /* TBD: Attenere la terminazione dei processi figli */

    remove_monitor_circolare(p);
    remove_monitor_buffer_singolo(b);

    /* TBD: Deallocare gli oggetti monitor */
}


void Produttore(MonitorVettoreCircolare *p, MonitorBufferSingolo *b) {

    int numero_elementi = rand() % 10;

    printf("[PRODUTTORE] Totale elementi da produrre: %d\n", numero_elementi);

    /* TBD: Effettuare una produzione su MonitorBufferSingolo con
            la funzione "produzione_buffer_singolo", inserendo "numero_elementi"
     */


    for(int i=0; i<numero_elementi; i++) {
    
        sleep(1);

        int val = rand() % 10;

        printf("[PRODUTTORE] Prodotto: %d\n", val);

        /* TBD: Chiamare la funzione "produzione_circolare" per produrre
                il valore "val"
         */
    }
}

void Consumatore(MonitorVettoreCircolare *p, MonitorBufferSingolo *b) {

    /* TBD: Effettuare una consumazione su MonitorBufferSingolo con
            la funzione "consumazione_buffer_singolo", prelevando "numero_elementi"
     */

    int numero_elementi = /* TBD */

    printf("[CONSUMATORE] Totale elementi da consumare: %d\n", numero_elementi);


    for(int i=0; i<numero_elementi; i++) {

        /* TBD: Chiamare la funzione "consumazione_circolare" per prelevare
                un valore e copiarlo in "val"
         */

        int val = /* TBD */

        printf("[CONSUMATORE] Consumato: %d\n", val);
    }
}
