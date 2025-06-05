#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header_msg.h"
#include "header_prodcons.h"


int main() {

    /* TBD: Ottenere gli identificativi delle code di messaggi */
    key_t k_mess = ftok(".", 'm');
    if (k_mess<0) die("ftok");

    key_t k_rts = ftok(".", 'r');
    if (k_rts<0) die("ftok");

    key_t k_ots = ftok(".", 'o');
    if (k_ots<0) die("ftok");

    int coda_mess = msgget(k_mess, 0);
    if (coda_mess<0) die("msgget");

    int coda_rts = msgget(k_rts, 0);
    if (coda_rts<0) die("msgget");

    int coda_ots = msgget(k_ots, 0);
    if (coda_ots<0) die("msgget");

    srand(getpid());

    for(int i=0; i<3; i++) {

        struct richiesta r;
        struct rts rts;
        struct ots ots;

        /* TBD: Inviare il messaggio "request to send" */
        rts.tipo = MESS;

        int ret = msgsnd(coda_rts, (void*)&rts, sizeof(rts)-sizeof(long), 0);
        if (ret<0) die("msgsnd");

        printf("[CLIENT] Inviato messaggio RTS\n");


        /* TBD: Ricevere il messaggio "ok to send" */
        ret = msgrcv(coda_ots, (void*)&ots, sizeof(ots)-sizeof(long), 0, 0);
        if (ret<0) die("msgrcv");

        printf("[CLIENT] Ricevuto messaggio OTS\n");


        int valore = rand() % 10;

        /* TBD: Inviare un messaggio con il valore */
        r.tipo = MESS;
        r.valore = valore;

        ret = msgsnd(coda_mess, (void*)&r, sizeof(r)-sizeof(long), 0);
        if (ret<0) die("msgsnd");

        printf("[CLIENT] Inviato messaggio MSG con valore %d\n", valore);

    }
}