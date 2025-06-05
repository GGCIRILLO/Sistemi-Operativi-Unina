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
#include <time.h>


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
                Wait_Sem(volo->id_sem, MUTEX);
                volo->num_lettori++;
                if (volo->num_lettori==1){
                        Wait_Sem(volo->id_sem, SYNCH);
                }
                Signal_Sem(volo->id_sem, MUTEX);
                
                //TODO: creazione e invio messaggio al visualizzatore
                msg m;
                m.volo = (long) volo->id_volo;
                m.gate = volo->gate;

                msgsnd(coda, (void*)&m, sizeof(msg)-sizeof(long), 0);

                printf("[%d]Lettore: messaggio inviato: volo = %ld, gate = %d\n",getpid(),m.volo,m.gate);

               
                sleep(1);

               //TODO: rilascio risorsa secondo soluzione lettori/scrittori, starvation scrittori
               Wait_Sem(volo->id_sem, MUTEX);
               volo->num_lettori--;
               if (volo->num_lettori==0){
                        Signal_Sem(volo->id_sem, SYNCH);
               }
               Signal_Sem(volo->id_sem, MUTEX);
        }

}

void Scrittore(Info_Volo* volo1, Info_Volo* volo2) {
        int i;
        srand(time(NULL)*getpid());

        for (i=0; i<NUM_OPERAZIONI; i++) {

                //TODO: accesso alle risorse secondo soluzione lettori/scrittori, starvation scrittori
                Wait_Sem(volo1->id_sem, SYNCH);
                Wait_Sem(volo2->id_sem, SYNCH);

                //TODO: gate del volo 2 = gate del volo 1
                //TODO: gate del volo 1 = valore casuale da 1 a 100 
                volo2->gate = volo1->gate;
                volo1->gate = rand()%100+1;

                printf("[%d] Scrittore: gate volo 1 = %d, gate volo 2 = %d\n", getpid(), volo1->gate, volo2->gate);

                sleep(1);

                //TODO: rilascio  risorse secondo soluzione lettori/scrittori, starvation scrittori
                Signal_Sem(volo1->id_sem, SYNCH);
                Signal_Sem(volo2->id_sem, SYNCH); 
        }

}


