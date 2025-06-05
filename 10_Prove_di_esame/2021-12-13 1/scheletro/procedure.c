#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"

int coda_RTS;
int coda_OTS;


void initServiceQueues(){

    /* TBD: inizializzazione code per implementare la send sincrona */
    coda_RTS = /* TBD */
    printf("Coda di servizio coda_RTS create con desc: %d\n", coda_RTS);
    
    coda_OTS = /* TBD */
    printf("Coda di servizio coda_OTS create con desc: %d\n", coda_OTS);
}

void removeServiceQueues(){
    /* TBD: rimozione code per implementare la send sincrona */
}


void controllore(int ds_queue_control_proxy){
    
    int i, ret;
    char citta_partenza[][20] = { "Napoli", "Roma", "Milano", "Torino", "Firenze"};
    char citta_destinazione[][20] = { "New York", "Madrid", "Londra", "Berlino", "Parigi"};
    
    Volo v_partenza;
    Volo v_arrivo;
    
    for (i=0; i<10; i++){
        
        /* TBD: Implementare lo scambio di messaggi necessario per
         * avere una send sincrona */
         
        
        if (i%2 == 0){
            
            /* TBD: Implementare invio messaggi per voli in ARRIVO */
            
        }else {

            /* TBD: Implementare invio messaggi per voli in PARTENZA */
        }
        
    }
    exit(0);
    
}
void proxy(int ds_queue_control_proxy, int ds_queue_proxy_gestori){
    
    int i, ret;
    Volo v;
    for (i=0; i<10; i++){
        
        /* TBD: Implementare lo scambio di messaggi necessario per
         * avere una send sincrona */
        
        /* TBD: Aggiungere la ricezione del volo vero e proprio */
        
        /* TBD: Aggiungere il codice per inviare opportunamente il volo
         * ricevuto al Gestore Arrivi o al Gestore Partenze
         */
        
    }
    exit(0);
}

void stampa_volo_info(Volo *v){
    
    printf("STAMPO INFO VOLO\n");
    printf("..........................ID: %d\n", v->ID);
    printf("..........................direzione: %s\n", v->direzione);
    printf("..........................citta_partenza: %s\n", v->citta_partenza);
    printf("..........................citta_arrivo: %s\n", v->citta_arrivo);
    
}

void gestore_arrivi(int ds_queue_proxy_gestori){
    
    int ret, i;
    Volo v;
    
    for (i=0; i<5; i++){
        
        /* TBD: Ricezione voli in ARRIVO */
        
        printf("\n\n****** ARRIVI ******\n\n");
        stampa_volo_info(&v);
    }
    exit(0);
}

void gestore_partenze(int ds_queue_proxy_gestori){
    
    int ret, i;
    Volo v;
    for (i=0; i<5; i++){
        
        /* TBD: Ricezione voli in PARTENZA */
        
        printf("\n\n****** PARTENZE ******\n\n");
        stampa_volo_info(&v);
    }
    exit(0);
}

