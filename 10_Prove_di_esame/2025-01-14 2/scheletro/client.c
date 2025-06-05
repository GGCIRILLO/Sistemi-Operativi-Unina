#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"

int main() {

    /* TBD: Ottenere i riferimenti alle code di messaggi */

    srand(getpid());

    for(int i=0; i<NUMERO_RICHIESTE; i++) {
        

        int tipo_richiesta;
        int valore;
        int posizione = rand() % DIM_VETTORE;

        if((rand() % 2) == 0) {

            tipo_richiesta = /* TBD */;
            valore = 0;
        }
        else {
            
            tipo_richiesta = /* TBD */;
            valore = rand() % 10;
        }

        printf("[CLIENT %d] Invio richiesta (tipo=%d, valore=%d, posizione=%d)\n", getpid(), tipo_richiesta, valore, posizione);

        /* TBD: Inviare un messaggio di richiesta */



        
        /* TBD: Ricevere il messaggio di risposta */

        int valore_risposta = /* TBD */;

        printf("[CLIENT %d] Ricezione risposta (valore=%d)\n", getpid(), valore_risposta);
    }


}