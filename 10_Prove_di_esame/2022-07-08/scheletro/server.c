#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "header.h"

typedef struct {
    int value;
    //TODO: aggiunta delle variabili necessarie alla sincronizzazione
    // con lettori-scrittori con staravtion di entrambi

} data_str;

typedef struct {
    int queue_res;
    int sender;
    data_str* data;
} reader_param;

int read_data(data_str* data) {
    int value;
    int my_id = syscall(SYS_gettid);
    
    //TODO: lettura valore da "data" attraverso
    // lettori-scrittori con starvation di entrambi
    
    value = data->value;
    printf("[%d]Lettore: il valore letto = %d\n",my_id,value);
    

    return value;
}

void write_data(data_str* data, int new_value) {
    //TODO: scrittura "new_value" in "data" attraverso
    // lettori-scrittori con starvation di entrambi
    int my_id = syscall(SYS_gettid);
    
    data->value = new_value;
    printf("[%d]Scrittore: il valore scritto = %d\n",my_id,data->value);
    
}

void * updater(void* par) {
	int my_id = syscall(SYS_gettid);
    data_str* data = (data_str*) par;
    int new_value;
    int i;
    for (i = 0; i < NUM_UPDATES; i++) {
        new_value = rand()%10+1;
        //printf("UPDATER[%d]: aggiornamento dato al valore: %d\n",my_id,new_value);
        write_data(data,new_value);
        sleep(rand()%3+1);
    }
    pthread_exit(NULL);
}

void * reader(void* par) {
    //TODO: ricostruzione parametro

	int my_id = syscall(SYS_gettid);
    res risp;
    //TODO: Costruzione risposta con prelievo valore dalla funzione read_data
    
    printf("READER_SERV[%d]: invio valore %d al client %ld\n",my_id,risp.value,risp.sender);
    //TODO: Invio risposta al reader client
    
   // printf("READER_SERV[%d]: valore %d al client %ld INVIATO\n",my_id,risp.value,risp.sender);

    pthread_exit(NULL);
}

int main() {

    int pid;
    key_t msg_req_key = //TODO: definire chiave
	key_t msg_res_key = //TODO: definire chiave

    //TODO: INIZIALIZZAZIONE CODE

    //TODO: inizializzazione struttura condivisa tra i thread

    //TODO: inizializzazione mutex e condition variables

    pthread_t upd, rd[NUM_READS*NUM_READERS];

    reader_param p[NUM_READS*NUM_READERS];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    srand(time(NULL));
    
    //TODO: creazione thread updater
    

    req msg;
    int i;
    for (i = 0; i < NUM_READS*NUM_READERS; i++) {
        //TODO: ricezione messaggio di richiesta
       
        printf("READER:SERV: ricevuta richiesta di lettura da: %d\n",msg.pid);
        //TODO: preparazione parametro p[i]
        
        //TODO: creazione thread reader
        
    }
    //TODO: join dei thread
    

    //TODO: deallocazione memoria e rimozione coda
    
    return 0;
}
