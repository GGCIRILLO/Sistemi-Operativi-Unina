#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header_msg.h"

int main() {

    /* TBD: Ottenere gli identificativi delle code di messaggi */


    srand(getpid());

    for(int i=0; i<3; i++) {

        struct richiesta r;
        struct rts rts;
        struct ots ots;

        /* TBD: Inviare il messaggio "request to send" */

        printf("[CLIENT] Inviato messaggio RTS\n");



        
        /* TBD: Ricevere il messaggio "ok to send" */

        printf("[CLIENT] Ricevuto messaggio OTS\n");


        int valore = rand() % 10;

        /* TBD: Inviare un messaggio con il valore */

        printf("[CLIENT] Inviato messaggio MSG con valore %d\n", valore);

    }
}