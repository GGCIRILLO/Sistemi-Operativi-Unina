#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "auth.h"

int main() {

    printf("Creazione code di messaggi\n");

    int id_coda_auth_req = /* TBD */

    int id_coda_auth_resp =/* TBD */
    
    int id_coda_elab_req = /* TBD */
    
    int id_coda_elab_resp = /* TBD */


    pid_t pid;


    printf("Avvio processo autenticatore\n");

    /* TBD: Avvio processo (funzione Auth) */
    


    printf("Avvio processo server\n");

    /* TBD: Avvio processo (funzione Server) */
	


    printf("Avvio processo client autenticato\n");

    /* TBD: Avvio processo (funzione ClientAuth) */
    
    

    printf("Avvio processo client non-autenticato\n");

    /* TBD: Avvio processo (funzione ClientNonAuth) */
    


    printf("Attesa terminazione processi\n");

    /* TBD: Attesa terminazione */
    


    printf("Rimozione code di messaggi\n");

    /* TBD: Rimozione code */ 

    return 0;
}
