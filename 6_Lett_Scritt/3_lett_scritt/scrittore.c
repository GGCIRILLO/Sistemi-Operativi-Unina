#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include "header.h"
#include "semafori.h"

static void die(const char* msg){
    perror(msg);
    exit(1);
}

int main() {

    // TODO: connetti a memoria condivisa e semafori con le stesse chiavi del padre
    key_t k_shm = ftok(".", 'A');
    key_t k_sem = ftok(".", 'B');

    int ds_shm = shmget(k_shm, sizeof(Buffer), 0); // Solo accesso
    if (ds_shm < 0) die("Errore shmget");

    int ds_sem = semget(k_sem, 4, 0); // Usa 4 semafori
    if (ds_sem < 0) die("Errore semget");

    Buffer *buffer = (Buffer *) shmat(ds_shm, NULL, 0);
    if (buffer == (void *) -1) die("Errore shmat");

    srand(time(NULL) ^ getpid());

    // TODO: ciclo di 5 scritture sincronizzate
    for (int i = 0; i < 5; i++) {
        int n1 = rand() % 10;
        int n2 = rand() % 10;

        // Inizio scrittura con priorità scrittori
        Wait_Sem(ds_sem, MUTEXS);
        buffer->numscrittori = buffer->numscrittori + 1;

        if (buffer->numscrittori == 1)
            Wait_Sem(ds_sem, SYNCH); // Primo scrittore blocca lettori

        Signal_Sem(ds_sem, MUTEXS);
        printf("[Sc] numS:%d , numL:%d\n", buffer->numscrittori, buffer->numlettori);


        Wait_Sem(ds_sem, MUTEX); // Accesso esclusivo alla scrittura

        // Scrittura dati
        buffer->val1 = n1;
        buffer->val2 = n2;

        sleep(1); // Simula scrittura

        printf("[Scrittore] Valori generati: %d, %d\n", n1, n2);

        Signal_Sem(ds_sem, MUTEX);

        // Fine scrittura
        Wait_Sem(ds_sem, MUTEXS);
        buffer->numscrittori = buffer->numscrittori-1;
        if (buffer->numscrittori == 0)
            Signal_Sem(ds_sem, SYNCH); // Ultimo scrittore sblocca lettori
        Signal_Sem(ds_sem, MUTEXS);
    }

    return 0;
}