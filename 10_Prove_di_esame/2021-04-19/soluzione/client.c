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
        msg_auth_req.type=TOKEN_AUTH_REQ_TYPE;
        msg_auth_req.PIDclient = getpid();

        ret = msgsnd(id_coda_auth_req, (void*)&msg_auth_req, sizeof(RichiestaAuth)-sizeof(long), 0);
        if (ret<0) die("msgsnd");

        printf("Client Auth (%d): attesa risposta auth\n", getpid());

        /* TBD: Ricezione messaggio con token */
        ret = msgrcv(id_coda_auth_resp, (void*)&msg_auth_resp, sizeof(RispostaAuth)-sizeof(long), MESSAGGIO_CLIENT, 0);
        if (ret<0) die("msgrcv");

        int token = msg_auth_resp.token; /* TBD */

        printf("Client Auth (%d): ricevuto token %d\n", getpid(), token);


        int valore = rand() % 11;

        printf("Client Auth (%d): invio richiesta elaborazione %d\n", getpid(), valore);

        /* TBD: Invio richiesta elaborazione */
        msg_elab_req.type = ELAB_REQ_TYPE;
        msg_elab_req.PID = getpid();
        msg_elab_req.valore= valore;
        msg_elab_req.token = token;
        ret = msgsnd(id_coda_elab_req, (void*)&msg_elab_req, sizeof(msg_elab_req)-sizeof(long), 0);
        if (ret<0) die("msgsnd");

        printf("Client Auth (%d): attesa risposta elaborazione\n", getpid());

        /* TBD: Ricezione risposta elaborazione */
        ret = msgrcv(id_coda_elab_resp, (void*)&msg_elab_resp, sizeof(msg_elab_resp)-sizeof(long), ELABORAZIONE, 0);
        if (ret<0) die("msgrcv");



        if(msg_elab_resp.esito == 1 /* TBD: condizione risposta con esito positivo */) {

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
        msg_elab_req.type = ELAB_REQ_TYPE;
        msg_elab_req.PID = getpid();
        msg_elab_req.valore= valore;
        msg_elab_req.token = token;
        ret = msgsnd(id_coda_elab_req, (void*)&msg_elab_req, sizeof(msg_elab_req)-sizeof(long), 0);
        if (ret<0) die("msgsnd");


        printf("Client Non-Auth (%d): attesa risposta elaborazione\n", getpid());

        /* TBD: Ricezione risposta elaborazione */
        ret = msgrcv(id_coda_elab_resp, (void*)&msg_elab_resp, sizeof(msg_elab_resp)-sizeof(long), ELABORAZIONE, 0);
        if (ret<0) die("msgrcv");


        if(msg_elab_resp.esito == 1 /* TBD: condizione risposta con esito positivo */) {

            printf("Client Non-Auth (%d): ricevuta risposta positiva\n", getpid());
        }
        else {
            printf("Client Non-Auth (%d): ricevuta risposta negativa\n", getpid());
        }

    }
}
