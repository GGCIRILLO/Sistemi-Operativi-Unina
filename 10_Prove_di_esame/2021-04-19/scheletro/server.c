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

        int valore = /* TBD */
        int PIDclient = /* TBD */
        int token = /* TBD */

        printf("Server: ricevuta richiesta %d da %d (token=%d)\n", valore, PIDclient, token);


        printf("Server: invio conferma autenticazione\n");

        /* TBD: Invio messaggio di richiesta conferma autenticazione */


        printf("Server: in attesa di conferma\n");

        /* TBD: Ricezione messaggio di risposta conferma autenticazione */ 


        int esito;

        if(/* TBD: condizione conferma autenticazione positivia */) {

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

    }

}
