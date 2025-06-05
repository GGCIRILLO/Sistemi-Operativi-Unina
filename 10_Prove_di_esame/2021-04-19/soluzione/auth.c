#include "auth.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pid_t pid;
    int token;
} autenticazione;


void Auth(int id_coda_auth_req, int id_coda_auth_resp) {

    RichiestaAuth msg_auth_req;
    RispostaAuth msg_auth_resp;

    int ret;

    autenticazione vettore_autenticazioni[10];
    int totale_autenticazioni = 0;


    for(int i=0; i<15; i++) {

        printf("Auth: in attesa di richieste\n");

        /* TBD: ricezione richieste */
        ret = msgrcv(id_coda_auth_req, (void*)&msg_auth_req, sizeof(msg_auth_req)-sizeof(long), 0, 0);
        if (ret<0) die("msgrcv");

        if(msg_auth_req.type==TOKEN_AUTH_REQ_TYPE /* TBD: richiesta di nuovo token */) {

            int token = rand() % 10000;

            pid_t PIDclient = msg_auth_req.PIDclient; /* TBD */ 

            vettore_autenticazioni[totale_autenticazioni].token = token;
            vettore_autenticazioni[totale_autenticazioni].pid = PIDclient;
            totale_autenticazioni++;

            printf("Auth: salvataggio token %d per processo %d\n", token, PIDclient);


            printf("Auth: invio token\n");

            /* TBD: Invio messaggio con token */
            //msg_auth_resp.esito = 1;
            msg_auth_resp.type = MESSAGGIO_CLIENT;
            msg_auth_resp.token=token;

            ret = msgsnd(id_coda_auth_resp, (void*)&msg_auth_resp, sizeof(msg_auth_resp)-sizeof(long), 0);
            if (ret<0) die("msgsnd");

        }
        else if(msg_auth_req.type==CONFERMA_AUTH_REQ_TYPE /* TBD: richiesta di conferma autenticazione */) {

            // Ricerca token nel vettore autenticazioni
            int trovato = -1;

            pid_t PIDclient = msg_auth_req.PIDclient; /* TBD */
            int token = msg_auth_req.token; /* TBD */ 


            for(int k=0; k<totale_autenticazioni; k++) {

                if(vettore_autenticazioni[k].pid == PIDclient &&
                    vettore_autenticazioni[k].token == token) {

                    printf("Auth: token di autenticazione di %d trovato\n", PIDclient);
                    trovato = k;
                    break;
                }
            }


            printf("Auth: invio messaggio di conferma autenticazione\n");

            if(trovato == -1) {

                /* TBD: Invio messaggio di autenticazione fallita//riuscita */
                msg_auth_resp.esito = 0;
            }
            else {

                /* TBD: Invio messaggio di autenticazione riuscita//fallita */
                msg_auth_resp.esito = 1;
            }

            msg_auth_resp.type = msg_auth_req.PIDserver;
            ret = msgsnd(id_coda_auth_resp, (void*)&msg_auth_resp, sizeof(msg_auth_resp)-sizeof(long), 0);
            if (ret<0) die("msgsnd");

        }
        else {
            printf("Auth: ricevuto messaggio di tipo errato\n");
        }
    }
}
