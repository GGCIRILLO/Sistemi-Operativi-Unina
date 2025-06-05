#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "header_msg.h"

int main() {

    /* TBD: Creare le code di messaggi */

    int id_queue_collettore_1 = /* TBD */;


    int id_queue_collettore_2 = /* TBD */;


    int id_queue_server = /* TBD */;


    /* TBD: Creare il processo figlio Server, 
            passandogli lo id della coda */


    int id_collettore = 1;

    /* TBD: Creare il primo processo figlio Collettore, 
            passandogli lo "id_collettore",
            lo id della coda per ricevere dai sensori,
            e lo id della coda per inviare al server
    */



    id_collettore = 2;
    
    /* TBD: Creare il secondo processo figlio Collettore, 
            passandogli lo "id_collettore",
            lo id della coda per ricevere dai sensori,
            e lo id della coda per inviare al server
    */


    for(int i=0; i<NUM_SENSORI_PER_COLLETTORE; i++) {

        int id_sensore = i+1;

        /* TBD: Creare i processi figli Sensore, 
                passandogli lo "id_sensore",
                e lo id della coda per inviare al primo collettore
        */

    }


    for(int i=0; i<NUM_SENSORI_PER_COLLETTORE; i++) {

        int id_sensore = i+1;

        /* TBD: Creare i processi figli Sensore, 
                passandogli lo "id_sensore",
                e lo id della coda per inviare al secondo collettore
        */
    }



    /* TBD: Attendere la terminazione di tutti i processi figli */


    /* TBD: De-allocare le code di messaggi */

    
    return 0;
}