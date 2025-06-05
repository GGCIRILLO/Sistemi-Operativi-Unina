#include <pthread.h>   // API POSIX Threads
#include <stdio.h>     // printf
#include <stdlib.h>    // exit

#define NUM_THREADS 5  // costante: numero di thread da creare

/* ------------------------------------------------------------------ *
 *  Funzione eseguita da ogni thread                                   *
 * ------------------------------------------------------------------ */
void *PrintHello(void *threadid)        // argomento generico (void*)
{
    /* Cast dell’argomento a long e stampa                       */
    printf("\n%ld: Hello World!\n", (long)threadid);

    /* Termina il thread e restituisce NULL al chiamante         */
    pthread_exit(NULL);
}

/* ------------------------------------------------------------------ *
 *  Funzione main (thread principale del processo)                     *
 * ------------------------------------------------------------------ */
int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];   // array di handle dei thread
    int rc;                           // codice di ritorno funzioni pthread
    long t;                           // indice usato come ID logico

    /* Ciclo di creazione dei thread --------------------------- */
    for (t = 0; t < NUM_THREADS; t++) {

        printf("Creating thread %ld\n", t);

        /* pthread_create:
         *  - &threads[t]  → dove salvare l’handle
         *  - NULL         → attributi di default
         *  - PrintHello   → funzione di start
         *  - (void *)t    → argomento passato al thread
         */
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);

        /* Se rc ≠ 0 è avvenuto un errore.                        */
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    /* IMPORTANTISSIMO:
     * pthread_exit nel thread principale impedisce che il processo
     * termini subito dopo il ciclo; attende implicitamente che TUTTI
     * i thread terminino (comportamento “join” automatizzato).
     */
    pthread_exit(NULL);
}