#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include "header.h"
#include "semafori.h"

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <variabile_da_leggere>\n", argv[0]);
        exit(1);
    }

    // TODO: leggere quale variabile leggere
    int variabile = atoi(argv[1]);
    if (variabile != 1 && variabile != 2) {
        printf("Errore: variabile deve essere 1 o 2.\n");
        exit(1);
    }

    // TODO: connetti a memoria e semafori
    key_t k_shm = ftok(".", 'A');
    key_t k_sem = ftok(".", 'B');

    int ds_shm = shmget(k_shm, sizeof(Buffer), 0);
    if (ds_shm < 0) die("Errore shmget");

    int ds_sem = semget(k_sem, 4, 0); // Usa 4 semafori
    if (ds_sem < 0) die("Errore semget");

    Buffer *buffer = (Buffer *) shmat(ds_shm, NULL, 0);
    if (buffer == (void *) -1) die("Errore shmat");

    // TODO: ciclo di 5 letture sincronizzate
    for (int i = 0; i < 5; i++) {

        // Inizio lettura
        Wait_Sem(ds_sem, MUTEXL);
        buffer->numlettori = buffer->numlettori +1;
        if (buffer->numlettori == 1)
            Wait_Sem(ds_sem, SYNCH); // Primo lettore blocca scrittori
        Signal_Sem(ds_sem, MUTEXL);

        printf("[Let] numS:%d , numL:%d\n", buffer->numscrittori, buffer->numlettori);

        // Lettura
        int val = (variabile == 1) ? buffer->val1 : buffer->val2;
        printf("[Lettore %d] Valore letto: %d\n", variabile, val);
        sleep(2); // Simula lettura

        // Fine lettura
        Wait_Sem(ds_sem, MUTEXL);
        buffer->numlettori = buffer->numlettori-1;
        if (buffer->numlettori == 0)
            Signal_Sem(ds_sem, SYNCH); // Ultimo lettore sblocca scrittori
        Signal_Sem(ds_sem, MUTEXL);
    }

    shmdt(buffer); // Buona pratica

    return 0;
}