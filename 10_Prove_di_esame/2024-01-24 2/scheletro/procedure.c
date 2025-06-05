#include "header_sem.h"

#include <stdio.h>
#include <stdlib.h>

int Wait_Sem (int id_sem, int numsem) {
       int err;
       struct sembuf sem_buf;

       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=-1;

       err = semop(id_sem,&sem_buf,1);   //semaforo rosso

       if(err<0) {
         perror("Errore WAIT");
         exit(0);
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
         perror("Errore SIGNAL");
         exit(0);
       }

       return err;
}


void scrivi(int id_sem, lettscritt * p, int valore) {

  Wait_Sem(id_sem, SYNCH);

  p->buffer = valore;

  Signal_Sem(id_sem, SYNCH);
}

int leggi(int id_sem, lettscritt * p) {

  Wait_Sem(id_sem, MUTEXL);

  p->num_lettori++;

  if(p->num_lettori == 1) {
    Wait_Sem(id_sem, SYNCH);
  }

  Signal_Sem(id_sem, MUTEXL);


  int valore = p->buffer;


  Wait_Sem(id_sem, MUTEXL);

  p->num_lettori--;

  if(p->num_lettori == 0) {
    Signal_Sem(id_sem, SYNCH);
  }

  Signal_Sem(id_sem, MUTEXL);


  return valore;

}