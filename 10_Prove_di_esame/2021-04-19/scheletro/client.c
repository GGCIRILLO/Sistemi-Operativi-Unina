#include "auth.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


void ClientAuth(int id_coda_auth_req, int id_coda_auth_resp, int id_coda_elab_req, int id_coda_elab_resp) {

    RichiestaAuth msg_auth_req;
    RispostaAuth msg_auth_resp;
    RichiestaElab msg_elab_req;
    RispostaElab msg_elab_resp;

    int ret;


    srand(time(NULL)*getpid());

    for(int i=0; i<5; i++) {


        printf("Client Auth (%d): invio richiesta auth\n", getpid());

        /* TBD: Invio messaggio richiesta nuovo token */


        printf("Client Auth (%d): attesa risposta auth\n", getpid());

        /* TBD: Ricezione messaggio con token */

        int token = /* TBD */

        printf("Client Auth (%d): ricevuto token %d\n", getpid(), token);


        int valore = rand() % 11;

        printf("Client Auth (%d): invio richiesta elaborazione %d\n", getpid(), valore);

        /* TBD: Invio richiesta elaborazione */



        printf("Client Auth (%d): attesa risposta elaborazione\n", getpid());

        /* TBD: Ricezione risposta elaborazione */



        if(/* TBD: condizione risposta con esito positivo */) {

            printf("Client Auth (%d): ricevuta risposta positiva\n", getpid());
        }
        else {
            printf("Client Auth (%d): ricevuta risposta negativa\n", getpid());
        }

    }
}

void ClientNonAuth(int id_coda_elab_req, int id_coda_elab_resp) {

    RichiestaElab msg_elab_req;
    RispostaElab msg_elab_resp;

    int ret;


    srand(time(NULL)*getpid());

    for(int i=0; i<5; i++) {

        int token = rand() % 10000; /* Token casuale non valido */
        int valore = rand() % 11;

        printf("Client Non-Auth (%d): invio richiesta elaborazione %d\n", getpid(), valore);

        /* TBD: Invio richiesta elaborazione */


        printf("Client Non-Auth (%d): attesa risposta elaborazione\n", getpid());

        /* TBD: Ricezione risposta elaborazione */



        if(/* TBD: condizione risposta con esito positivo */) {

            printf("Client Non-Auth (%d): ricevuta risposta positiva\n", getpid());
        }
        else {
            printf("Client Non-Auth (%d): ricevuta risposta negativa\n", getpid());
        }

    }
}
