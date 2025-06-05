#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include "header.h"
#include "semafori.h"

static void die(const char *msg){
    perror(msg);
    exit(1);
}

int main() {
    // TODO: creare shared memory (shmget) e salvarne l'id
    key_t k_shm = ftok(".", 'A');
    int ds_shm = shmget(k_shm, sizeof(Buffer), IPC_CREAT|0664);
    if (ds_shm<0) die("Errore shmget");

    // TODO: creare semafori (semget) e salvarne l'id
    key_t k_sem = ftok(".", 'B');
    int ds_sem = semget(k_sem, 4, IPC_CREAT |0664);
    if(ds_sem<0) die("Errore semget");

    // TODO: inizializzare i valori iniziali del buffer 
    Buffer * buffer = (Buffer*) shmat(ds_shm, NULL, 0);
    if(buffer==(void*)-1) die("Errore shmat");
    buffer->val1 = 0;
    buffer->val2 = 0;
    buffer->numlettori = 0;
    buffer->numscrittori = 0;

    // TODO: inizializzare i semafori con semctl (es. SYNCH = 1, MUTEXL = 1)
    semctl(ds_sem, SYNCH, SETVAL, 1);
    semctl(ds_sem, MUTEXL, SETVAL, 1);
    semctl(ds_sem, MUTEXS, SETVAL, 1);
    semctl(ds_sem, MUTEX, SETVAL, 1);

    // TODO: creare 3 processi figli con fork()
    //       - il primo esegue scrittore (exec)
    //       - gli altri due eseguono lettore (uno per val1, uno per val2)
    //       - passare 1 o 2 come argomento per differenziare i lettori

    pid_t pid;

    // Processo scrittore
    pid = fork();
    if (pid == 0) {
        execl("./scrittore", "scrittore", (char *)NULL);
        die("Errore exec scrittore");
    }

    // Primo processo lettore (legge val1)
    pid = fork();
    if (pid == 0) {
        execl("./lettore", "lettore", "1", (char *)NULL); // 1 = leggi val1
        die("Errore exec lettore1");
    }

    // Secondo processo lettore (legge val2)
    pid = fork();
    if (pid == 0) {
        execl("./lettore", "lettore", "2", (char *)NULL); // 2 = leggi val2
        die("Errore exec lettore2");
    }

    // TODO: attendere la terminazione dei figli con wait()
    for (int i=0;i<3;i++) wait(NULL);

    // TODO: deallocare memoria condivisa e semafori
    shmctl(ds_shm, IPC_RMID, 0);
    semctl(ds_sem, 0, IPC_RMID);

    return 0;
}