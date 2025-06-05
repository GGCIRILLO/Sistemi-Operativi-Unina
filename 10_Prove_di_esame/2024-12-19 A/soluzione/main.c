#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "header.h"

#define NUM_CONSUMI 10

int main() {

    /*
        TODO: inizializzazione segmenti di memoria e strutture condivisi
    */
    int id_shm = shmget(IPC_PRIVATE, sizeof(MonitorProdCons), IPC_CREAT|0664);
    if (id_shm<0) die("shmget");

    MonitorProdCons * m = (MonitorProdCons*) shmat(id_shm, NULL, 0);
    if (m==(void*)-1) die("shmat");

    inizializza_vettore(m);

    int id_shm_bb = shmget(IPC_PRIVATE, sizeof(BufferBabbo), IPC_CREAT|0664);
    if (id_shm_bb<0) die("shmget");

    BufferBabbo * b = (BufferBabbo*) shmat(id_shm_bb, NULL, 0);
    if (b==(void*)-1) die("shmat");

    inizializza_buffer(b);

    pid_t pid_p, pid_c1, pid_c2, pid_b;

    /*
        TODO: creazione di 4 figli: un Produttore, un Consumatore1, un Consumatore2 e BabboNatale
    */
    pid_p= fork();
    if (pid_p<0) die("fork");
    else if (pid_p==0) {
        Produttore(m);
        exit(0);
    }

    pid_c1= fork();
    if (pid_c1<0) die("fork");
    else if (pid_c1==0){
        Consumatore1(m, b);
        exit(0);
    }

    pid_c2= fork();
    if (pid_c2<0) die("fork");
    else if (pid_c2==0){
        Consumatore2(m, b);
        exit(0);
    }

    pid_b= fork();
    if (pid_b<0) die("fork");
    else if (pid_b==0){
        BabboNatale(b);
        exit(0);
    }

    /*
        TODO: attesa terminazione figli
    */
    while(wait(NULL)>0);

    /*
        TODO: distruzione strutture
    */
    rimuovi_vettore(m);
    shmctl(id_shm, IPC_RMID, NULL);

    rimuovi_buffer(b);
    shmctl(id_shm_bb, IPC_RMID, NULL);

    return 0;
}