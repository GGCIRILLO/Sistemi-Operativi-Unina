#include "header_sem.h"
#include <unistd.h>

int Wait_Sem (int id_sem, int numsem) {
       int err;
       struct sembuf sem_buf;

       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=-1;

       err = semop(id_sem,&sem_buf,1);   //semaforo rosso

       if(err<0) {
        char msg[80];
        snprintf(msg, sizeof msg,
                 "Errore WAIT (set=%d, sem=%d)", id_sem, numsem);
         perror(msg);
       }

       return err;
}


int Signal_Sem (int id_sem, int numsem) {
       int err;
       struct sembuf sem_buf;

       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=1;

       err = semop(id_sem,&sem_buf,1);   //semaforo verde

       if(err<0) {
        char msg[80];
        snprintf(msg, sizeof msg,
                 "Errore SIGNAL (set=%d, sem=%d)", id_sem, numsem);
         perror(msg);
       }

       return err;
}

void produci(int id_sem, prodcons * p, int valore) {

    /* TBD: Implementare il codice del produttore */
    Wait_Sem(id_sem, SPAZIO_DISPONIBILE);

    Wait_Sem(id_sem, MUTEXP);

    sleep(2);

    p->buffer[p->testa] = valore;

    p->testa = (p->testa+1) % DIM;

    Signal_Sem(id_sem, MUTEXP);

    Signal_Sem(id_sem, MESSAGGIO_DISPONIBILE);
    
}

int consuma(int id_sem, prodcons * p) {
	int valore;
    /* TBD: Implementare il codice del consumatore */
  
  Wait_Sem(id_sem, MESSAGGIO_DISPONIBILE);

  Wait_Sem(id_sem, MUTEXC);

  sleep(2);

  valore = p->buffer[p->coda];

  p->coda = (p->coda+1) % DIM;

  Signal_Sem(id_sem, MUTEXC);

  Signal_Sem(id_sem, SPAZIO_DISPONIBILE);
  
  return valore;
}
