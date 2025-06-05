#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"

void cliente(posto * teatro, int * disponibilita, int semid) {
    sleep(rand()%6);

    int n = rand()%4 + 1;
    int array[4];

    Wait_Sem(semid, MUTEX);

    if (*disponibilita < n) {
        printf("Disponibilità esaurita\n");
        Signal_Sem(semid, MUTEX);
        exit(1);
    }

    int i=0, j=0;
    while (j<DIM_POSTI && i<n) {
        if (teatro[j].stato == LIBERO) {
            teatro[j].stato = IN_AGGIORNAMENTO;
            array[i] = j;
            i++;
        }
        j++;
    }

    // A questo punto sono stati riservati i posti
    *disponibilita -= n;

    Signal_Sem(semid, MUTEX);

    sleep(1); // Tempo di prenotazione

    Wait_Sem(semid, MUTEX);

    for (int i=0; i<n; i++) {
        teatro[array[i]].stato = OCCUPATO;
        teatro[array[i]].id_cliente = getpid();
    }

    printf("Cliente PID=%d ha prenotato %d posti\n", getpid(), n);

    Signal_Sem(semid, MUTEX);

    exit(0); // chiudere SEMPRE con exit
}