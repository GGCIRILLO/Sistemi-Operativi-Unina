#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"

int main() {

    /* TBD: Ottenere i riferimenti alle code di messaggi */
    key_t k_req_cl_serv = ftok(".", 'a');
    if (k_req_cl_serv<0) die("ftok");

    int id_coda_req_cl_serv = msgget(k_req_cl_serv, 0);
    if (id_coda_req_cl_serv<0) die("msgget");

    key_t k_res_cl_serv = ftok(".", 'b');
    if (k_res_cl_serv<0) die("ftok");

    int id_coda_res_cl_serv = msgget(k_res_cl_serv, 0);
    if (id_coda_res_cl_serv<0) die("msgget");


    srand(getpid());

    for(int i=0; i<NUMERO_RICHIESTE; i++) {
        

        int tipo_richiesta;
        int valore;
        int posizione = rand() % DIM_VETTORE;

        if((rand() % 2) == 0) {

            tipo_richiesta = LETTURA /* TBD */;
            valore = 0;
        }
        else {
            
            tipo_richiesta = SCRITTURA/* TBD */;
            valore = rand() % 10;
        }

        printf("[CLIENT %d] Invio richiesta (tipo=%d, valore=%d, posizione=%d)\n", getpid(), tipo_richiesta, valore, posizione);

        /* TBD: Inviare un messaggio di richiesta */
        messaggio_richiesta m;
        m.tipo = tipo_richiesta;
        m.valore = valore;
        m.pid_mittente = getpid();
        m.posizione = posizione;

        int ret = msgsnd(id_coda_req_cl_serv, (void*)&m, sizeof(m)-sizeof(long), 0);
        if (ret<0) die("msgsnd");
        
        /* TBD: Ricevere il messaggio di risposta */
        messaggio_risposta msg;

        ret = msgrcv(id_coda_res_cl_serv, (void*)&msg, sizeof(msg)-sizeof(long), getpid(), 0);
        if (ret<0) die("msgrcv");

        int valore_risposta = msg.valore /* TBD */;

        printf("[CLIENT %d] Ricezione risposta (valore=%d)\n", getpid(), valore_risposta);
    }


}