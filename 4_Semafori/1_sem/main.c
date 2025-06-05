#include <stdio.h>
#include <sys/types.h>   /* tipi base di sistema e fork()/wait()          */
#include <sys/wait.h>    /* wait(), waitpid()                             */
#include <sys/ipc.h>     /* chiavi IPC (key_t)                            */
#include <sys/shm.h>     /* System-V shared memory                        */
#include <sys/sem.h>     /* System-V semaphores                           */
#include <unistd.h>      /* fork(), getpid()                              */
#include <stdlib.h>      /* exit(), EXIT_FAILURE                          */
#include <errno.h>       /* errno                                         */

#include "semafori.h"    /* wrapper con Wait_Sem() e Signal_Sem()         */

/*--------------------------------------------------------------------------*/
/* Wrapper locale per la gestione errori; riduce ripetizioni nel codice.    */
static void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
/*--------------------------------------------------------------------------*/

int main(void)
{
    /*----------------------------------------------------------------------
     * 1. Creazione delle risorse IPC
     *----------------------------------------------------------------------*/

    /* Con IPC_PRIVATE (=0) la risorsa è “privata” al processo che la crea
     * e — grazie a fork() — a tutti i suoi figli.  Non può invece essere
     * aperta da processi estranei lanciati separatamente.
     */
    key_t k_shmem = IPC_PRIVATE;   /* chiave per la memoria condivisa  */
    key_t k_sem   = IPC_PRIVATE;   /* chiave per il set di semafori    */

    /* --- Segmento di memoria condivisa --------------------------------- */
    /* sizeof(int) byte, flag IPC_CREAT (crea se non esiste),
     * permessi 0664  (rw-rw-r–).                                          */
    int id_shmem = shmget(k_shmem, sizeof(int), IPC_CREAT | 0664);
    if (id_shmem < 0) die("shmget");

    /* --- Set di semafori ------------------------------------------------ */
    /* nsems = 1 -> un solo semaforo nel set (indice 0). */
    int id_sem = semget(k_sem, 1, IPC_CREAT | 0664);
    if (id_sem < 0) die("semget");

    /*----------------------------------------------------------------------
     * 2. Aggancio del segmento e inizializzazione del semaforo
     *----------------------------------------------------------------------*/

    /* shmat() “mappa” il segmento nello spazio di indirizzi del processo
     * restituendo un puntatore C utilizzabile come memoria normale.
     */
    int *shared = shmat(id_shmem, NULL, 0);
    if (shared == (void *)-1) die("shmat");

    /* semctl SETVAL: inizializza il semaforo #0 a 1 → lock libero. */
    if (semctl(id_sem, 0, SETVAL, 1) < 0) die("semctl SETVAL");

    printf("[PARENT] semaforo %d inizializzato a 1\n", id_sem);

    *shared = 0;                              /* contatore iniziale     */
    printf("[PARENT] valore iniziale = %d\n", *shared);

    /*----------------------------------------------------------------------
     * 3. Creazione di due processi figli
     *----------------------------------------------------------------------*/
    for (int i = 0; i < 2; i++) {

        pid_t pid = fork();

        if (pid < 0) die("fork");

        /*--------------------------  FIGLIO  ------------------------------*/
        if (pid == 0) {
            printf("[CHILD %d] pid=%d avviato\n", i, getpid());

            /* Ogni figlio esegue 100 incrementi protetti.                  */
            for (int j = 0; j < 100; j++) {

                /* ==== fase di ingresso: acquisisce il mutex ============= */
                Wait_Sem(id_sem, 0);      /* P-operation (sem_op = -1)      */

                /* =======  SEZIONE CRITICA  (accesso esclusivo)  ========= */
                int tmp = *shared;        /* legge il valore corrente       */
                tmp += 1;                 /* calcola il nuovo valore        */
                *shared = tmp;            /* scrive                        */
                /* ======================================================== */

                /* ==== fase di uscita: rilascia il mutex ================= */
                Signal_Sem(id_sem, 0);    /* V-operation (sem_op = +1)      */
            }

            /* Fine del lavoro del figlio: esce — il padre farà cleanup.   */
            exit(EXIT_SUCCESS);
        }
        /* Il padre ritorna al for per creare (eventualmente) il 2° figlio */
    }

    /*----------------------------------------------------------------------
     * 4. Attesa del termine di entrambi i figli
     *----------------------------------------------------------------------*/
    for (int i = 0; i < 2; i++)
        wait(NULL);           /* si blocca finché ogni figlio non termina   */

    /* A questo punto i due figli hanno completato 2 × 100 = 200 incrementi */
    printf("[PARENT] valore finale = %d\n", *shared);

    /*----------------------------------------------------------------------
     * 5. Pulizia (rimozione) delle risorse IPC
     *----------------------------------------------------------------------*/

    /* shmctl IPC_RMID stacca *e rimuove* il segmento dal kernel           */
    if (shmctl(id_shmem, IPC_RMID, NULL) < 0) die("shmctl IPC_RMID");

    /* semctl IPC_RMID rimuove l’intero set di semafori                    */
    if (semctl(id_sem, 0, IPC_RMID) < 0) die("semctl IPC_RMID");

    return 0;
}