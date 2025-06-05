#include "processi.h"
#include "semafori.h"   /* fornisce Wait_Sem / Signal_Sem             */

#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

static void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
/*---------------------------------------------------------------*/
int inizializza_semafori(void)
{
    /* TODO: allocare un set di 1 semaforo binario con semget()
     *       e inizializzarlo a 1 con semctl().
     *       In caso di errore, stampare perror e exit.
     */
    int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0664);
    if (sem_id<0) die("Errore semget");
    int res = semctl(sem_id, 0, SETVAL, 1);
    if(res<0) die("Errore semctl");

    return sem_id; 
}

/*---------------------------------------------------------------*/
void figlio(int *vettore,
            long long *buffer,
            int sem_id,
            int elemento_iniziale,
            int qta_elementi)
{
    /* TODO: 1) calcolare la somma parziale della propria fetta
     *       2) Aggiornare il buffer
     *       3) Fare attenzione alla zona critica
     */
     long long somma = 0;
     for (int i= elemento_iniziale; i<elemento_iniziale + qta_elementi; i++){
        somma+=vettore[i];
     }

     printf("[Figlio PID=%d] Somma parziale: %lld\n", getpid(), somma);

     Wait_Sem(sem_id, 0);

     *buffer += somma;

     Signal_Sem(sem_id, 0);

}

/*---------------------------------------------------------------*/
void padre(long long *buffer, int sem_id)
{
    /* TODO: attendere la terminazione di tutti i figli con wait()
     *       quindi stampare somma totale e media aritmetica.
     */

    for (int i=0;i<N_CHILD;i++) wait(NULL);

    printf("[PADRE] Somma totale: %lld\n", *buffer);

    double m = (double) (*buffer)/N_ELEM;

    printf("[PADRE] Media aritmetica: %.3f\n", m);
}