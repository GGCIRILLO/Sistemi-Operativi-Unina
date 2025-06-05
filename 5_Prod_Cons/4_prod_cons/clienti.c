#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "procedure.h"  // Importa le funzioni da procedure.c

static void die(const char* msg){
    perror(msg);
    exit(1);
}

int main() {

    // TODO: Creare chiave IPC privata
    key_t k = ftok(".", 'A');

    // TODO: Allocare shared memory abbastanza grande per 80 posti + disponibilita
    int ds_shm = shmget(k, sizeof(struct shm_data), IPC_CREAT|0664);
    if (ds_shm<0) die("Errore shmget");

    // TODO: Attaccare la shared memory
    struct shm_data * p = (struct shm_data *) shmat(ds_shm, NULL, 0);
    if (p==(void*)-1) die("Errore shmat");

    // TODO: Inizializzare tutti i posti a stato LIBERO e id_cliente 0
    for (int i=0;i<DIM_POSTI;i++){
        p->teatro[i].id_cliente = 0;
        p->teatro[i].stato=LIBERO;
    }

    // TODO: Inizializzare disponibilita a 80
    p->disponibilita = DIM_POSTI;

    printf("Teatro inizializzato con %d posti disponibili\n", DIM_POSTI);

    key_t k_sem = ftok(".", 'B'); // Semaforo

    // TODO: Creare un semaforo MUTEX (1 semaforo)
    int ds_sem = semget(k_sem, 1, IPC_CREAT|0664);
    if (ds_sem<0) die("Errore semget");

    // TODO: Inizializzare MUTEX a 1
    if(semctl(ds_sem, MUTEX, SETVAL, 1)<0) die("Errore semctl");


    // TODO: Creare 50 processi figli con fork()

    // In ogni figlio:
    // - Stampare "Avvio figlio cliente PID=..."
    // - Chiamare la funzione cliente() (definita in procedure.c)
    // - Terminare il processo con exit()

    for (int i=0;i<NUM_FIGLI;i++){
        pid_t pid = fork();
        if (pid<0) die("Errore fork");
        if(pid==0){
            printf("Avvio Figlio cliente PID=%d\n", getpid());
            srand(getpid()*time(NULL));
            cliente(p->teatro, &(p->disponibilita), ds_sem);
            exit(1);
        }
    }

    // TODO: Attendere la terminazione di tutti i figli (wait())
    for (int i = 0; i < NUM_FIGLI; i++) {
    int status;
    pid_t pid = wait(&status);

    if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        printf("[PADRE] Terminato PID figlio = %d con exit code %d\n", pid, exit_code);
    }
}

    // TODO: Deallocare shared memory
    shmctl(ds_shm, IPC_RMID, NULL);
    
    // TODO: Deallocare semaforo
    semctl(ds_sem, 0, IPC_RMID);

    return 0;
}