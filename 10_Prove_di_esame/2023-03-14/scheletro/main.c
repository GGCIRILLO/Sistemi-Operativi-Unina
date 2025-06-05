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
     key_t c_mem=/***/;
     Info_Volo *volo1, *volo2;
     // ...
     //TODO inizializzare id_volo pari a 1 per volo1 e pari a 2 per volo2
     

     //TODO: compleare richiesta semafori ed inizializzazione
     key_t c_sem=/***/;
     // ...

     //TODO: compleatare richiesta coda messaggi
     key_t c_coda=/***/;
     // ...
     
     //TODO generazione tramite fork di scrittore e 4 lettori, 2 per il volo 1 e 2 per il volo 2
    
     //TODO generazione tramite fork/exec del visualizzatore
     

     //TODO: attesa terminazione dei "numprocessi"  figli
     int numprocessi = NUM_LETTORI+2;
    

     //TODO: Deallocazione risorse

     return 0;
}
