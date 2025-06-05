#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"


/*******PROCEDURE PER I SEMAFORI******/


void Wait_Sem(int id_sem, int numsem)     {
       struct sembuf sem_buf;
       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=-1;
       semop(id_sem,&sem_buf,1);   //semaforo rosso
}


  void Signal_Sem (int id_sem,int numsem)     {
       struct sembuf sem_buf;
       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=1;
       semop(id_sem,&sem_buf,1);   //semaforo verde
}


/***********************************************/

void Lettore(Info_Volo *volo, int coda){
	int i;
        for (i=0; i<NUM_OPERAZIONI; i++) {

                //TODO: accesso alla risorsa secondo soluzione lettori/scrittori, starvation scrittori
                
                //TODO: creazione e invio messaggio al visualizzatore

               
                sleep(1);

               //TODO: rilascio risorsa secondo soluzione lettori/scrittori, starvation scrittori

        }

}

void Scrittore(Info_Volo* volo1, Info_Volo* volo2) {
        int i;
        for (i=0; i<NUM_OPERAZIONI; i++) {

                //TODO: accesso alle risorse secondo soluzione lettori/scrittori, starvation scrittori 
                //TODO: gate del volo 2 = gate del volo 1
                //TODO: gate del volo 1 = valore casuale da 1 a 100 
                sleep(1);
                //TODO: rilascio  risorse secondo soluzione lettori/scrittori, starvation scrittori 
        }

}


