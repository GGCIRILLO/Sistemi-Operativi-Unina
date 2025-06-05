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
    int key_req = ftok(".", 'a');
    int key_res = ftok(".", 'b');
    int coda_richieste = msgget(key_req, 0);
    int coda_risposte = msgget(key_res, 0);

    if (coda_richieste == -1 || coda_risposte == -1) {
        perror("Errore nell'apertura delle code");
        exit(1);
    }

    for (int i = 0; i < NUM_BAMBINI; i++) {
        /* TODO */
        pid_t pid = fork();
        if (pid==0){
            srand(time(NULL)*getpid());
            for (int j = 0; j < NUM_LETTERE; j++) {
                /*
                    TODO: costruzione e invio del messaggio
                */
                MessaggioRichiesta msg;
                msg.tipo=1;


                /* TODO */ msg.numero_regali = (rand() % 5) + 1;

                msgsnd(coda_richieste, (void*)&msg, sizeof(MessaggioRichiesta)-sizeof(long), 0);

                printf("Invio lettera a Babbo Natale chiedendo %d regali\n", msg.numero_regali);

                /*
                    TODO: attesa del messaggio di risposta
                */
                MessaggioRisposta m;
                msgrcv(coda_risposte, (void*)&m, sizeof(MessaggioRisposta)-sizeof(long), 0, 0);
                printf("[Bambino %d] Lettera %d: conferma ricevuta\n", i + 1, j + 1);
            }
            exit(0);
        }
    }

    /*
        TODO: Attesa della terminazione dei processi figli
    */
    while(wait(NULL)>0);

    return 0;
}
