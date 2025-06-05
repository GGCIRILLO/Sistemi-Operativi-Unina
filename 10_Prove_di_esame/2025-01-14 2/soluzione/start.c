#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"

int main() {

    /* TBD: Creare le code di messaggi */
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


    for(int i=0; i<PROCESSI_CLIENT; i++) {
        
        /* TBD: Creare i processi client */
        pid_t pid = fork();
        if (pid<0) die("fork");
        else if(pid==0){
            execl("./client", "client", NULL);
            die("execl");
        }

    }


    for(int i=0; i<PROCESSI_SERVER; i++) {
        
        /* TBD: Creare i processi server */
        pid_t pid = fork();
        if (pid<0) die("fork");
        else if(pid==0){
            execl("./server", "server", NULL);
            die("execl");
        }
    }


    /* TBD: Creare il processo database */
    pid_t pid = fork();
    if (pid<0) die("fork");
    else if (pid==0){
        execl("./database", "database", NULL);
    }


    /* TBD: Attendere e gestire la terminazione */
    while(wait(NULL)>0);

    msgctl(id_coda_req_cl_serv, 0, IPC_RMID);
    msgctl(id_coda_res_cl_serv, 0, IPC_RMID);


    return 0;

}