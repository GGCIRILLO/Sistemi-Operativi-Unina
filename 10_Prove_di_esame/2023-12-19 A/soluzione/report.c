#include <stdio.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "teatro.h"

int main(){
    
    //Creazione code tra Buyer e Report
    int ds_queue_viewer;
    
    //create queues
    int key_queue_viewer = ftok(".", 'c'); /* TODO: ottenere chiave per la coda di comunicazione tra viewers e report */
    
    ds_queue_viewer = msgget(key_queue_viewer, 0); /* TODO: ottenere il descrittore per la coda di comunicazione tra viewers e report */
    
    printf("[report] Coda ds_queue_viewer ID: %d\n", ds_queue_viewer);
    
    Msg_Posto m_posto;
    
    int count_platea = 0, count_balconata = 0;
    
    int i, ret;
    
    for (i=0; i<20; i++){
        
        ret = msgrcv(ds_queue_viewer, (void*)&m_posto, sizeof(Msg_Posto)-sizeof(long), 0, 0); /* TODO: ricezione messaggio sulla coda */
        if (ret<0){
            perror("Errore rcv ds_queue_viewer");
            exit(-1);
        }
        if (m_posto.value == 0)
            count_platea ++;
        else if (m_posto.value == 1)
            count_balconata++;
    }
    
    printf("Count posti PLATEA: %d\n", count_platea);
    printf("Count posti BALCONATA: %d\n", count_balconata);
    
    return 0;
}


