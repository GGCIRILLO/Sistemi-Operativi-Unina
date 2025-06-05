#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "header.h"


int main(){

    
     //TODO: completare richiesta shared memory ed inizializzazione
     key_t c_mem= IPC_PRIVATE /***/;
     Info_Volo *volo1, *volo2;
     // ...
     int shm = shmget(c_mem, sizeof(Info_Volo)*2, IPC_CREAT|0664);

     volo1 = (Info_Volo*) shmat(shm, NULL, 0);

     volo2 = volo1+1;

     volo1->num_lettori=0;

     volo2->num_lettori=0;

     //TODO inizializzare id_volo pari a 1 per volo1 e pari a 2 per volo2
     volo1->id_volo = 1;
     volo2->id_volo = 2;

     //TODO: compleare richiesta semafori ed inizializzazione
     key_t c_sem = IPC_PRIVATE /***/;
     // ...
     int sem1 = semget(c_sem, 2, IPC_CREAT|0664);
     semctl(sem1, SYNCH, SETVAL, 1);
     semctl(sem1, MUTEX, SETVAL, 1);
     volo1->id_sem = sem1;

     int sem2 = semget(c_sem, 2, IPC_CREAT|0664);
     semctl(sem2, SYNCH, SETVAL, 1);
     semctl(sem2, MUTEX, SETVAL, 1);
     volo2->id_sem = sem2;

     //TODO: compleatare richiesta coda messaggi
     key_t c_coda= ftok(".", 'c') /***/;
     // ...
     int coda = msgget(c_coda, IPC_CREAT|0664);
     
     //TODO generazione tramite fork di scrittore e 4 lettori, 2 per il volo 1 e 2 per il volo 2
     pid_t pid = fork();
     if (pid == 0)
     {
          printf("[%d] Inizio Scrittore\n", getpid());
          Scrittore(volo1, volo2);
          exit(0);
     }
     for (int i = 0; i < NUM_LETTORI; i++)
     {
          pid = fork();
          if (pid == 0)
          {
               if (i%2==0) {
                    printf("[%d] Inizio Lettore volo 1\n", getpid());
                    Lettore(volo1, coda);
               } else {
                    printf("[%d] Inizio Lettore volo 2\n", getpid());
                    Lettore(volo2, coda);
               }
               exit(0);
          }
     }
    
     //TODO generazione tramite fork/exec del visualizzatore
     pid = fork();
     if (pid == 0) {
          printf("[%d] Inizio Visualizzatore\n", getpid());
          execl("./visualizzatore", "visualizzatore", NULL);
          perror("execl");
          exit(1);
     }

     //TODO: attesa terminazione dei "numprocessi"  figli
     int numprocessi = NUM_LETTORI+2;
     while(wait(NULL)>0);

     //TODO: Deallocazione risorse
     semctl(sem1, 0 ,IPC_RMID);
     semctl(sem2, 0 ,IPC_RMID);
     shmctl(shm, IPC_RMID , 0);
     msgctl(coda, IPC_RMID , 0);

     return 0;
}
