#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>      
#include "processi.h"          /* costanti e prototipi                      */

static void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void)
{
    /*------------------------------------------------------------------
     * 1. Creazione della shared memory per il vettore di 10 000 interi
     *------------------------------------------------------------------
     *    • usare shmget() con IPC_PRIVATE e dimensione N_ELEM * sizeof(int)
     *    • mappare con shmat() per ottenere un puntatore (int *) vettore
     */

    /* TODO */
    int array_id = shmget(IPC_PRIVATE, N_ELEM*sizeof(int), IPC_CREAT | 0664);
    if (array_id<0) die("Errore shmget");

    int * array = shmat(array_id, NULL, 0);

    if (array == (void*)-1) die("Errore shmat");


    /*------------------------------------------------------------------
     * 2. Inizializzare il vettore con valori casuali (0–999)
     *------------------------------------------------------------------
     *    • srand(time(NULL))
     *    • ciclare su N_ELEM elementi
     */

    /* TODO */
    srand(time(NULL));

    for (int i = 0; i < N_ELEM; i++)
    {
        array[i] = rand() % 1000;
    }


    /*------------------------------------------------------------------
     * 3. Creazione della shared memory per il buffer long long (somma)
     *------------------------------------------------------------------
     *    • shmget() + shmat() per un solo long long
     *    • inizializzare il buffer a 0
     */

    /* TODO */

    int buff_id = shmget(IPC_PRIVATE, sizeof(long long), IPC_CREAT|0664);
    if (buff_id<0) die("Errore buff shmget");
    long long * buff = shmat(buff_id, NULL, 0);
    if(buff==(void*)-1) die("Errore buff shmat");

    *buff = 0;

    /*------------------------------------------------------------------
     * 4. Inizializzazione semaforo di mutua esclusione
     *------------------------------------------------------------------
     *    • chiamare inizializza_semafori() (da implementare)
     */

    int sem_id = inizializza_semafori();

    /*------------------------------------------------------------------
     * 5. Creazione dei processi figli
     *------------------------------------------------------------------
     *    • ciclo da 0 a N_CHILD–1
     *        – fork()
     *        – nel figlio chiamare figlio(vettore, buffer, sem_id,
     *                                     index * CHUNK, CHUNK)
     *        – exit immediato del figlio dopo la chiamata
     */

    /* TODO */
    for (int i=0;i<N_CHILD;i++){
        int pid = fork();
        if (pid<0) die("Errore fork");
        else if(pid==0){
            figlio(array, buff, sem_id, i*CHUNK, CHUNK);
            exit(0);
        }
    }

    /*------------------------------------------------------------------
     * 6. Codice del padre
     *------------------------------------------------------------------
     *    • chiamare padre(buffer, sem_id) per:
     *        – attendere i figli
     *        – stampare somma totale e media
     */

    padre(buff, sem_id);

    /*------------------------------------------------------------------
     * 7. Pulizia risorse IPC
     *------------------------------------------------------------------
     *    • semctl(... IPC_RMID)
     *    • shmctl(... IPC_RMID) per vettore e buffer
     */

    /* TODO */

    semctl(sem_id, 0, IPC_RMID);
    shmctl(array_id, IPC_RMID, 0);
    shmctl(buff_id, IPC_RMID, 0);

    return 0;
}