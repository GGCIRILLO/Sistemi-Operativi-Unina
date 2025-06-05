#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#include "header_prodcons.h"
#include "header_msg.h"
#include "semafori.h"


void ricevi_da_collettore(int id_queue_server, BufferProdCons * b);
void visualizza(BufferProdCons * b);
void produci_valore(BufferProdCons * b, int valore);
int consuma_valore(BufferProdCons * b);

int main () {

    int sem_key = /*TODO*/;
    int sem_id = /*TODO*/;
    //TODO inizializzazione semafori

    //TODO inizializzazione struttura condivisa
    BufferProdCons * b = /*TODO*/;

    key_t chiave_server = /*TODO*/;
    int id_queue_server = /*TODO*/;


    //TODO: Creazione processo "ricevi_da_collettore"
    
    //TODO: Creazione 2 processi "visualizza"

    //TODO: attesa processi figli

    //TODO: rimozione risorse IPC
    return 0;
}

void ricevi_da_collettore(int id_queue_server, BufferProdCons * b){

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE; i++) {

        //TODO: ricezione messaggio con media da collettore

        int media = /*TODO*/;

        produci_valore(b, media);

    }

}

void visualizza(BufferProdCons * b) {

    for(int i=0; i<NUM_MESSAGGI_PER_SENSORE/2; i++) {
        sleep(2);
        int media = consuma_valore(b);

        printf("[SERVER] Visualizzo valore medio corrente=%d\n", media);
    
    }

}


void produci_valore(BufferProdCons * b, int valore) {

    //TODO: implementare produttore

}

int consuma_valore(BufferProdCons * b) {

    //TODO: implementare consumatore

}
