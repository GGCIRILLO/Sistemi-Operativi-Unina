#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

#include "header_msg.h"
#include "header_sem.h"


void server(/* TBD: Completare il passaggio dei parametri */ int id_sem, lettscritt * p) {

    for(int i=0; i<10; i++) {

        sleep(1);

        int valore = leggi(id_sem, p /* TBD */);

        printf("[SERVER WORKER %d] Letto valore %d\n", getpid(), valore);

    }

}

int main() {


    /* TBD: Ottenere gli identificativi delle code di messaggi */
    int q_mess = queue_create('M');   // messaggio 
    int q_rts  = queue_create('R');   // Ready-To-Send            
    int q_ots  = queue_create('O');   // Ok-To-Send    



    int sem[NUM_BUFFER];
    int shm[NUM_BUFFER];
    lettscritt * ls[NUM_BUFFER];


    for(int i=0; i<NUM_BUFFER; i++) {

        /* TBD: Allocare il buffer su memoria condivisa */
        key_t k_shm = ftok(".", 's'+i);

        int ds_shm =  shmget(k_shm, sizeof(lettscritt), IPC_CREAT|0664);
        if (ds_shm<0) die("shmget");

        ls[i] = (lettscritt*) shmat(ds_shm, NULL, 0) /* TBD */;
        if (ls[i] == (lettscritt*)-1) die("shmat");
        ls[i]->num_lettori = 0;
        ls[i]->buffer = 0;

        shm[i] = ds_shm /* TBD */;



        printf("[SERVER FRONTEND %d] Creato buffer %d (p=%p, id=%d)\n", getpid(), i, ls[i], shm[i]);


        key_t k_sem = ftok(".", 'S'+i);
        int ds_sem = semget(k_sem, NSEM, IPC_CREAT|0664);
        if (ds_sem<0) die("semget");
        if (semctl(ds_sem, SYNCH, SETVAL, 1) < 0) die("semctl");
        if (semctl(ds_sem, MUTEXL, SETVAL, 1) < 0) die("semctl");

        sem[i] = ds_sem /* TBD */;


        printf("[SERVER FRONTEND %d] Creato vettore semafori %d (id=%d)\n", getpid(), i, sem[i]);

    }


    for(int i=0; i<NUM_SERVER; i++) {

        /* TBD: 
            Creare un processo figlio (server worker),
            e fargli eseguire la funzione "server()".

            Passare al worker il riferimento
            a uno dei buffer e ai relativi semafori.

            Esempio: allo i-esimo processo server worker
            dovrà essere passato il semaforo "sem[i % NUM_BUFFER]".
        */
        pid_t pid_server = fork();
        if (pid_server == 0) {
            // Processo figlio
            server(sem[i % NUM_BUFFER], ls[i % NUM_BUFFER]);
            exit(0);
        } else if (pid_server < 0) die("fork");

        printf("[SERVER FRONTEND %d] Creato processo server worker %d (pid=%d)\n", getpid(), i, pid_server);

    }



    for(int i=0; i<NUM_RICHIESTE; i++) {

        /* TBD: Effettuare la ricezione del messaggio dal client (send sincrona) */
        service_msg m1, m2;
        msg m;

        msgrcv(q_rts, &m1, sizeof(service_msg) - sizeof(long), RTS, 0);
        m2.type = OTS;
        strcpy(m2.desc, "Ready to send");
        msgsnd(q_ots, &m2, sizeof(service_msg) - sizeof(long), 0);

        msgrcv(q_mess, &m, sizeof(msg) - sizeof(long), MESSAGGIO, 0);

        int buffer = m.buff_id /* TBD */;
        int value = m.val /* TBD */;

        printf("[SERVER FRONTEND %d] Ricevuto richiesta (valore=%d, buffer=%d)\n", getpid(), value, buffer);

        /* TBD: Completare il passaggio dei parametri.
                Passare alla funzione i riferimenti allo
                i-esimo buffer e ai relativi semafori.
         */

        scrivi(sem[buffer], ls[buffer], value /* TBD */);
    }


    /* TBD: Attendere la terminazione dei processi figli e deallocare le risorse */
    while(wait(NULL)>0);

    for (int i = 0; i < NUM_BUFFER; ++i) {
        semctl(sem[i], 0, IPC_RMID);
        shmctl(shm[i], IPC_RMID, NULL);
    }


    return 0;
}