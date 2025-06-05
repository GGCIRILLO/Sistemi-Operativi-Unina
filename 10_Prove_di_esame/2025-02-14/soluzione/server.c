#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#include "header_prodcons.h"
#include "header_msg.h"
#include "semafori.h"


void ricevi_da_collettore(int id_queue_server, BufferProdCons * b);
void visualizza(BufferProdCons * b);
void produci_valore(BufferProdCons * b, int valore);
int consuma_valore(BufferProdCons * b);

int main () {

    int sem_key = IPC_PRIVATE /*TODO*/;
    int sem_id = semget(sem_key, 4, IPC_CREAT|0664) /*TODO*/;
    if (sem_id<0) die("semget");

    //TODO inizializzazione semafori
    semctl(sem_id, SPAZIO, SETVAL, DIM_BUFF);
    semctl(sem_id, MESS, SETVAL, 0);
    semctl(sem_id, MUTEXC, SETVAL, 1);
    semctl(sem_id, MUTEXP, SETVAL, 1);

    //TODO inizializzazione struttura condivisa
    int id_shm = shmget(IPC_PRIVATE, sizeof(BufferProdCons), IPC_CREAT|0664);
    if (id_shm<0) die("shmget");

    BufferProdCons * b = (BufferProdCons*) shmat(id_shm, NULL, 0) /*TODO*/;
    if (b==(void*)-1) die("shmat");

    b->sem_id = sem_id;
    b->testa =  0;
    b->coda = 0;

    key_t chiave_server = ftok(".", 's') /*TODO*/;
    if (chiave_server<0) die("ftok");

    int id_queue_server = msgget(chiave_server, 0) /*TODO*/;
    if (id_queue_server<0) die("msgget");


    //TODO: Creazione processo "ricevi_da_collettore"
    pid_t pid = fork();
    if (pid<0) die("fork");
    else if (pid==0){
        printf("[SERVER] Avvio Ricezione da collettore\n");
        ricevi_da_collettore(id_queue_server, b);
        exit(0);
    }
    
    //TODO: Creazione 2 processi "visualizza"
    for (int i=0;i<2;i++){
        pid_t pid_vis = fork();
        if (pid_vis<0) die("fork");
        else if (pid_vis==0){
            printf("[SERVER] Avvio Visualizzatore\n");
            visualizza(b);
            exit(0);
        }
    }

    //TODO: attesa processi figli
    while(wait(NULL)>0);

    printf("[SERVER] Processi figli terminati\n");

    //TODO: rimozione risorse IPC
    semctl(b->sem_id, 0 , IPC_RMID);
    shmctl(id_shm, IPC_RMID, NULL);
    msgctl(id_queue_server, IPC_RMID, NULL);

    return 0;
}

void ricevi_da_collettore(int id_queue_server, BufferProdCons * b){

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        //TODO: ricezione messaggio con media da collettore
        messaggio_collettore m;
        int ret = msgrcv(id_queue_server, (void*)&m, sizeof(messaggio_collettore)-sizeof(long), TIPO_MESSAGGIO, 0);
        if (ret<0) die("msgrcv");

        int media = m.media /*TODO*/;

        printf("[SERVER] Ricevuto media: %d\n", media);

        produci_valore(b, media);

    }

}

void visualizza(BufferProdCons * b) {

    pid_t pid = getpid();

    // Per distinguere i due visualizzatori
    int id_vis = pid % 2;

    int n = (id_vis==0) ? 3 : 2;

    for(int i=0; i<n; i++) {
        sleep(2);
        int media = consuma_valore(b);

        printf("[SERVER] Visualizzo valore medio corrente=%d\n", media);
    
    }

}


void produci_valore(BufferProdCons * b, int valore) {

    //TODO: implementare produttore
    Wait_Sem(b->sem_id, SPAZIO);

    Wait_Sem(b->sem_id, MUTEXP);

    b->valore[b->testa] = valore;
    b->testa = (b->testa + 1) % DIM_BUFF;

    printf("[SERVER-PRODUTTORE] Prodotto valore %d\n", valore);

    Signal_Sem(b->sem_id, MUTEXP);

    Signal_Sem(b->sem_id, MESS);


}

int consuma_valore(BufferProdCons * b) {

    //TODO: implementare consumatore
    Wait_Sem(b->sem_id, MESS);

    Wait_Sem(b->sem_id, MUTEXC);

    int res = b->valore[b->coda];
    b->coda = (b->coda+1)%DIM_BUFF;

    printf("[SERVER-CONSUMATORE] Consumato valore %d\n", res);

    Signal_Sem(b->sem_id, MUTEXC);

    Signal_Sem(b->sem_id, SPAZIO);

    return res;
}
