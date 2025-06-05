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
    coda_RTS = msgget(IPC_PRIVATE, IPC_CREAT|0664); /* TBD */
    printf("Coda di servizio coda_RTS create con desc: %d\n", coda_RTS);
    
    coda_OTS = msgget(IPC_PRIVATE, IPC_CREAT|0664); /* TBD */
    printf("Coda di servizio coda_OTS create con desc: %d\n", coda_OTS);
}

void removeServiceQueues(){
    /* TBD: rimozione code per implementare la send sincrona */
    msgctl(coda_RTS, IPC_RMID, NULL);
    msgctl(coda_OTS, IPC_RMID, NULL);

    printf("Rimosse Code di servzio\n");
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
        Control m1, m2;
        m1.tipo = REQUEST_TO_SEND;

        ret = msgsnd(ds_queue_control_proxy, (void*)&m1, sizeof(Control)-sizeof(long), 0);
        if (ret<0){
            perror("msgsnd");
            exit(1);
        }
        ret = msgrcv(ds_queue_control_proxy, (void*)&m2, sizeof(Control)-sizeof(long), OK_TO_SEND, 0);
        if (ret<0){
            perror("msgrcv");
            exit(1);
        }
         
        srand(time(NULL)*getpid());

        if (i%2 == 0){
            
            /* TBD: Implementare invio messaggi per voli in ARRIVO */
            v_arrivo.tipo = MSG_TYPE_CONTROL_PROXY;
            v_arrivo.ID = i;
            strcpy(v_arrivo.direzione, "ARRIVO");
            strcpy(v_arrivo.citta_partenza, citta_destinazione[rand()%5]);
            strcpy(v_arrivo.citta_arrivo, citta_partenza[rand()%5]);
            
            ret = msgsnd(ds_queue_control_proxy, (void*)&v_arrivo, sizeof(Volo)-sizeof(long), 0);

            printf("Controllore: Inviato volo in ARRIVO con ID: %d\n", v_arrivo.ID);
        }else {

            /* TBD: Implementare invio messaggi per voli in PARTENZA */
                        v_partenza.tipo = MSG_TYPE_CONTROL_PROXY;
            v_partenza.ID = i;
            strcpy(v_partenza.direzione, "PARTENZA");
            strcpy(v_partenza.citta_partenza, citta_partenza[rand()%5]);
            strcpy(v_partenza.citta_arrivo, citta_destinazione[rand()%5]);

            ret = msgsnd(ds_queue_control_proxy, (void*)&v_partenza, sizeof(Volo)-sizeof(long), 0);

            printf("Controllore: Inviato volo in PARTENZA con ID: %d\n", v_partenza.ID);
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
        Control m1, m2;
        ret = msgrcv(ds_queue_control_proxy, (void*)&m1, sizeof(Control)-sizeof(long), REQUEST_TO_SEND, 0);
        if (ret<0){
            perror("msgrcv");
            exit(1);
        }

        m2.tipo = OK_TO_SEND;
        ret = msgsnd(ds_queue_control_proxy, (void*)&m2, sizeof(Control)-sizeof(long), 0);
        if (ret<0){
            perror("msgsnd");
            exit(1);
        }

        /* TBD: Aggiungere la ricezione del volo vero e proprio */
        ret = msgrcv(ds_queue_control_proxy, (void*)&v, sizeof(Volo)-sizeof(long), MSG_TYPE_CONTROL_PROXY, 0);
        if (ret<0){
            perror("msgrcv");
            exit(1);
        }
        
        printf("Proxy: Ricevuto volo con ID: %d\n", v.ID);

        /* TBD: Aggiungere il codice per inviare opportunamente il volo
         * ricevuto al Gestore Arrivi o al Gestore Partenze
         */
        if (strcmp(v.direzione, "ARRIVO") == 0){
            v.tipo = MSG_TYPE_ARRIVI;
        
            printf("Proxy: Inviato volo in ARRIVO con ID: %d\n", v.ID);
        } else if (strcmp(v.direzione, "PARTENZA") == 0){
            v.tipo = MSG_TYPE_PARTENZE;
            
            printf("Proxy: Inviato volo in PARTENZA con ID: %d\n", v.ID);
        }

        msgsnd(ds_queue_proxy_gestori, (void*)&v, sizeof(Volo)-sizeof(long), 0);
        
    }
    exit(0);
}

void stampa_volo_info(Volo *v){
    
    printf("STAMPO INFO VOLO\n");
    printf("..........................ID: %d\n", v->ID);
    printf("..........................direzione: %s\n", v->direzione);
    printf("..........................citta_partenza: %s\n", v->citta_partenza);
    printf("..........................citta_arrivo: %s\n\n", v->citta_arrivo);
    
}

void gestore_arrivi(int ds_queue_proxy_gestori){
    
    int ret, i;
    Volo v;
    
    for (i=0; i<5; i++){
        
        /* TBD: Ricezione voli in ARRIVO */
        ret = msgrcv(ds_queue_proxy_gestori, (void*)&v, sizeof(Volo)-sizeof(long), MSG_TYPE_ARRIVI, 0);
        if (ret<0){
            perror("msgrcv");
            exit(1);
        }

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
        ret = msgrcv(ds_queue_proxy_gestori, (void*)&v, sizeof(Volo)-sizeof(long), MSG_TYPE_PARTENZE, 0);
        if (ret<0){
            perror("msgrcv");
            exit(1);
        }
        
        printf("\n\n****** PARTENZE ******\n\n");
        stampa_volo_info(&v);
    }
    exit(0);
}

