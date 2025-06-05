#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

#include "header.h"

void inizializza(MonitorCoda *p) {

    /* TBD: Aggiungere codice per l'inizializzazione del monitor e delle relative
     * variabili per la sincronizzazione
     */
    

}

void rimuovi(MonitorCoda * p) {
    /* TBD: Aggiungere codice per la rimozione del monitor */
}


int produzione(MonitorCoda *p, int valore) {

    /* TBD: Aggiungere codice per la produzione in accordo allo schema
     * con vettore di stato, ricordando che il valore di ritorno della funzione
     * indica se il monitor è sovraccarico o meno.
     * Nel caso in cui ci siano almeno 4 produttori in attesa, bisogna forzare
     * l'uscita del processo dal monitor e ritornare un valore pari ad 1.
     * Nel caso in cui la produzione avviene normalmente ritornare un valore pari a 0.
     */
}


/* NOTA: il valore di ritorno di consumazione() è il valore prelevato dalla coda */

int consumazione(MonitorCoda *p) {


    /* TBD: Aggiungere codice per la consumazione in accordo allo schema
     * con vettore di stato, ricordando che il valore di ritorno della funzione
     * indica il valore prelevato dal buffer condiviso.
     */

}

void produttore(MonitorCoda *m) {
    
    int valore;
    int ret;
    int i;
    
    for(i=0; i<5; i++) {
        
        while(1) {
            
            srand(time(NULL)*getpid());
            
            valore = rand() % 10;
            
            ret = produzione(m, valore);
            
            if(ret==0) { break; }
            
            printf("MONITOR SOVRACCARICO, ATTENDO 3 secondi...\n");
            
            sleep(3);
        }
        
        printf("VALORE PRODOTTO: %d\n", valore);
        
        sleep(1);
    }
    
    
    exit(0);
}

void consumatore(MonitorCoda *m) {
    
    int i;
    int valore;
    
    for(i=0; i<15; i++) {
        
        valore = consumazione(m);
        
        printf("VALORE CONSUMATO: %d\n", valore);
        
        sleep(2);
    }
    
    
    exit(0);
}

