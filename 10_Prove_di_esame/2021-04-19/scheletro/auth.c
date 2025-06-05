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

        if(/* TBD: richiesta di nuovo token */) {

            int token = rand() % 10000;

            pid_t PIDclient = /* TBD */ 

            vettore_autenticazioni[totale_autenticazioni].token = token;
            vettore_autenticazioni[totale_autenticazioni].pid = PIDclient;
            totale_autenticazioni++;

            printf("Auth: salvataggio token %d per processo %d\n", token, PIDclient);


            printf("Auth: invio token\n");

            /* TBD: Invio messaggio con token */

            //msg_auth_resp.esito = 1;
 

        }
        else if(/* TBD: richiesta di conferma autenticazione */) {

            // Ricerca token nel vettore autenticazioni
            int trovato = -1;

            pid_t PIDclient = /* TBD */
            int token =/* TBD */ 


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
            }
            else {

                /* TBD: Invio messaggio di autenticazione riuscita//fallita */
            }



        }
        else {
            printf("Auth: ricevuto messaggio di tipo errato\n");
        }
    }
}
