#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"

int main() {

    /* TBD: Ottenere i riferimenti alle code di messaggi */




    for(int i=0; i<NUMERO_RICHIESTE; i++) {

        /* TBD: Ricevere un messaggio di richiesta dal client */

        int tipo_richiesta = /* TBD */;
        int valore = /* TBD */;
        int posizione = /* TBD */;
        int pid_client = /* TBD */;

        printf("[SERVER %d] Inoltro richiesta (tipo=%d, pid=%d, posizione=%d, valore=%d)\n", getpid(), tipo_richiesta, pid_client, posizione, valore);

        sleep(1);


        /* TBD: Inviare un messaggio di richiesta al database, contenente lo stesso tipo di richiesta (LETTURA/SCRITTURA), posizione, e valore */




        /* TBD: Ricevere un messaggio di risposta dal database */

        int valore_risposta = /* TBD */;

        printf("[SERVER %d] Inoltro risposta (pid=%d, valore=%d)\n", getpid(), pid_client, valore_risposta);



        /* TBD: Inviare il messaggio di risposta al client, contenente lo stesso valore risposta */



    }

}