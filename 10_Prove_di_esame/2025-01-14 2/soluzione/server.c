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

    int id_coda_req_cl_serv = msgget(k_req_cl_serv, IPC_CREAT|0664);
    if (id_coda_req_cl_serv<0) die("msgget");

    key_t k_res_cl_serv = ftok(".", 'b');
    if (k_res_cl_serv<0) die("ftok");

    int id_coda_res_cl_serv = msgget(k_res_cl_serv, IPC_CREAT|0664);
    if (id_coda_res_cl_serv<0) die("msgget");

    key_t k_req_serv_db = ftok(".", 'c');
    if (k_req_serv_db<0) die("ftok");

    int id_coda_req_serv_db = msgget(k_req_serv_db, IPC_CREAT|0664);
    if (id_coda_req_serv_db<0) die("msgget");    

    key_t k_res_serv_db = ftok(".", 'd');
    if (k_res_serv_db<0) die("ftok");

    int id_coda_res_serv_db = msgget(k_res_serv_db, IPC_CREAT|0664);
    if (id_coda_res_serv_db<0) die("msgget");



    for(int i=0; i<NUMERO_RICHIESTE; i++) {

        /* TBD: Ricevere un messaggio di richiesta dal client */
        messaggio_richiesta m;
        int ret = msgrcv(id_coda_req_cl_serv, (void*)&m, sizeof(m)-sizeof(long), 0, 0);
        if (ret<0) die("msgrcv");

        int tipo_richiesta = m.tipo /* TBD */;
        int valore = m.valore /* TBD */;
        int posizione = m.posizione /* TBD */;
        int pid_client = m.pid_mittente /* TBD */;

        printf("[SERVER %d] Inoltro richiesta (tipo=%d, pid=%d, posizione=%d, valore=%d)\n", getpid(), tipo_richiesta, pid_client, posizione, valore);

        sleep(1);


        /* TBD: Inviare un messaggio di richiesta al database, contenente lo stesso tipo di richiesta (LETTURA/SCRITTURA), posizione, e valore */
        m.pid_mittente = getpid();
        ret = msgsnd(id_coda_req_serv_db, (void*)&m, sizeof(m)-sizeof(long), 0);
        if (ret<0) die("msgsnd");

        /* TBD: Ricevere un messaggio di risposta dal database */
        messaggio_risposta msg;
        ret = msgrcv(id_coda_res_serv_db, (void*)&msg, sizeof(messaggio_risposta)-sizeof(long), getpid(), 0);
        if (ret<0) die("msgrcv");

        int valore_risposta = msg.valore /* TBD */;

        printf("[SERVER %d] Inoltro risposta (pid=%d, valore=%d)\n", getpid(), pid_client, valore_risposta);



        /* TBD: Inviare il messaggio di risposta al client, contenente lo stesso valore risposta */
        msg.tipo = pid_client;
        ret = msgsnd(id_coda_res_cl_serv, (void*)&msg, sizeof(msg)-sizeof(long), 0);
        if (ret<0) die("msgsnd");


    }

}