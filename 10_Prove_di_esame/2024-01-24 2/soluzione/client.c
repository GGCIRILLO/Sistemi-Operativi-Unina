#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

#include "header_msg.h"
#include "header_sem.h"


int main() {

    srand(getpid());


    /* TBD: Ottenere gli identificativi delle code di messaggi */
    int q_mess = queue_create('M');   // messaggio 
    int q_rts  = queue_create('R');   // Ready-To-Send            
    int q_ots  = queue_create('O');   // Ok-To-Send    



    for(int i=0; i<NUM_RICHIESTE; i++) {

        int buffer = rand() % NUM_BUFFER;

        int value = rand() % 10;


        /* TBD: Inviare un messaggio contenente "value" e "buffer".

                È richiesto che l'invio sia effettuato
                tramite send sincrona.
         */

        service_msg m1, m2;
        msg m;
        m1.type = RTS;
        strcpy(m1.desc, "Richiesta di invio");
        msgsnd(q_rts, &m1, sizeof(service_msg) - sizeof(long), 0);
         
        msgrcv(q_ots, &m2, sizeof(service_msg) - sizeof(long), OTS, 0);

        m.type = MESSAGGIO;
        m.val = value;
        m.buff_id = buffer;

        msgsnd(q_mess, &m, sizeof(msg) - sizeof(long), 0);
        printf("[CLIENT %d] Inviato valore %d al buffer %d\n", getpid(), value, buffer);


        sleep(2);

    }

}