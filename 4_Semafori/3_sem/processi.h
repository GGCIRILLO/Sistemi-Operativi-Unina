#ifndef PROCESSI_H
#define PROCESSI_H
/*---------------------------------------------------------------
 * Costanti di configurazione
 *-------------------------------------------------------------*/
#define N_ELEM     10000          /* dimensione del vettore intero   */
#define N_CHILD    10             /* numero di processi figli        */
#define CHUNK      (N_ELEM / N_CHILD)   /* elementi gestiti da ogni figlio */


int inizializza_semafori(void);


void figlio(int *vettore,
            long long *buffer,
            int sem_id,
            int elemento_iniziale,
            int qta_elementi);


void padre(long long *buffer,
           int sem_id);

#endif /* PROCESSI_H */