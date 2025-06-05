#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include "header.h"

int main() {
    /*
        TODO: recupero code
    */

    if (coda_richieste == -1 || coda_risposte == -1) {
        perror("Errore nell'apertura delle code");
        exit(1);
    }

    for (int i = 0; i < NUM_BAMBINI; i++) {
        /* TODO */
            srand(time(NULL)*getpid());
            for (int j = 0; j < NUM_LETTERE; j++) {
                /*
                    TODO: costruzione e invio del messaggio
                */

                /* TODO */ = (rand() % 5) + 1;

                printf("Invio lettera a Babbo Natale chiedendo %d regali\n", msg.numero_regali);

                /*
                    TODO: attesa del messaggio di risposta
                */
                printf("[Bambino %d] Lettera %d: conferma ricevuta\n", i + 1, j + 1);
            }
            exit(0);
        }
    }

    /*
        TODO: Attesa della terminazione dei processi figli
    */

    return 0;
}
