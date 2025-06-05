#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "auth.h"

void Server(int id_coda_elab_req, int id_coda_elab_resp, int id_coda_auth_req, int id_coda_auth_resp) {

    RichiestaAuth msg_auth_req;
    RispostaAuth msg_auth_resp;
    RichiestaElab msg_elab_req;
    RispostaElab msg_elab_resp;

    int ret;

    int risorsa = 0;


    for(int i=0; i<10; i++) {

        printf("Server: in attesa di richieste\n");

        /* TBD: Ricezione messaggi di richiesta elaborazione */
        ret = msgrcv(id_coda_elab_req, (void*)&msg_elab_req, sizeof(msg_elab_req)-sizeof(long), ELAB_REQ_TYPE, 0);
        if (ret<0) die("msgrcv");


        int valore = msg_elab_req.valore; /* TBD */
        int PIDclient = msg_elab_req.PID; /* TBD */
        int token = msg_elab_req.token; /* TBD */

        printf("Server: ricevuta richiesta %d da %d (token=%d)\n", valore, PIDclient, token);


        printf("Server: invio conferma autenticazione\n");

        /* TBD: Invio messaggio di richiesta conferma autenticazione */
        msg_auth_req.type = CONFERMA_AUTH_REQ_TYPE;
        msg_auth_req.token = token;
        msg_auth_req.PIDclient = PIDclient;
        msg_auth_req.PIDserver = getpid();

        ret = msgsnd(id_coda_auth_req, (void*)&msg_auth_req, sizeof(msg_auth_req)-sizeof(long), 0);
        if (ret<0) die("msgsnd");


        printf("Server: in attesa di conferma\n");

        /* TBD: Ricezione messaggio di risposta conferma autenticazione */
        ret = msgrcv(id_coda_auth_resp, (void*)&msg_auth_resp, sizeof(msg_auth_resp)-sizeof(long), getpid(), 0);
        if (ret<0) die("msgrcv"); 



        int esito;

        if(msg_auth_resp.esito==1 /* TBD: condizione conferma autenticazione positivia */) {

            printf("Server: autenticazione del client %d riuscita\n", PIDclient);

            risorsa = valore;

            printf("Server: nuovo valore risorsa = %d\n", risorsa);

            esito = 1;
        }
        else {

            printf("Server: autenticazione del client %d fallita\n", PIDclient);
 
            esito = 0;
        }

        printf("Server: invio risposta al client\n");

        /* TBD: Invio messaggio di risposta elaborazione, con esito positivo o negativo */
        msg_elab_resp.type = ELABORAZIONE;
        msg_elab_resp.esito = esito;

        ret = msgsnd(id_coda_elab_resp, (void*)&msg_elab_resp, sizeof(msg_elab_resp)-sizeof(long), 0);
        if (ret<0) die("msgsnd");

    }

}
