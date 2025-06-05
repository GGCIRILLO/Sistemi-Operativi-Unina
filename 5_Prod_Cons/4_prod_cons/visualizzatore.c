#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "procedure.h"  // Importa le funzioni da procedure.c
#include "semafori.h"
static void die(const char * msg){
    perror(msg);
    exit(1);
}

int main() {

    // TODO: Connettersi alla shared memory creata dai clienti
    key_t k = ftok(".", 'A'); // Shared memory
    int ds_shm = shmget(k, sizeof(struct shm_data), 0664);
    if (ds_shm<0) die("Errore shmget visualizzatore");
    struct shm_data * p = (struct shm_data *) shmat(ds_shm, NULL, 0);
    if (p==(void*)-1) die("Errore shmat visualizzatore");

    // TODO: Connettersi al semaforo MUTEX
    key_t k_sem = ftok(".", 'B'); // Semaforo       
    int ds_sem = semget(k_sem, 1, 0);
    if (ds_sem<0) die("Errore semget visualizzatore");

    while (1) {

        // TODO: Attendere 1 secondo (sleep(1))
        sleep(1);

        // TODO: Wait(MUTEX)
        Wait_Sem(ds_sem, MUTEX);

        // TODO: Stampare a video la situazione aggiornata dei posti:
        // per ogni posto: numero, stato (LIBERO/OCCUPATO/IN AGGIORNAMENTO), id_cliente se occupato
        for (int i=0;i<DIM_POSTI;i++){
            printf("Posto N %d :", i);
            if (p->teatro[i].stato==0){
               printf("LIBERO\n");
            } else if (p->teatro[i].stato == 1){
                printf("OCCUPATO da %d\n", p->teatro[i].id_cliente);
            } else{
                printf("IN AGGIORNAMENTO\n");
            }
        }

        printf("\n\n");

        // TODO: Verificare se disponibilita == 0
        // Se sì, uscire dal ciclo
        if (p->disponibilita==0) {
            Signal_Sem(ds_sem, MUTEX);
            break;
        }

        // TODO: Signal(MUTEX)
        Signal_Sem(ds_sem, MUTEX);
    }

    return 0;
}