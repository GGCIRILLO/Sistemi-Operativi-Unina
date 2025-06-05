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
    int num_lett;
    int scrittore_attivo;
    int scrittori_attesa;
    pthread_mutex_t mutex;
    pthread_cond_t cv_lett;
    pthread_cond_t cv_scritt;
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
    pthread_mutex_lock(&data->mutex);

    while(data->scrittore_attivo){
        pthread_cond_wait(&data->cv_lett, &data->mutex);
    }
    data->num_lett++;
    pthread_mutex_unlock(&data->mutex);
    
    value = data->value;
    printf("[%d]Lettore: il valore letto = %d\n",my_id,value);
    
    pthread_mutex_lock(&data->mutex);

    data->num_lett--;
    if (data->num_lett==0){
        pthread_cond_signal(&data->cv_scritt);
    }

    pthread_mutex_unlock(&data->mutex);
    
    return value;
}

void write_data(data_str* data, int new_value) {
    //TODO: scrittura "new_value" in "data" attraverso
    // lettori-scrittori con starvation di entrambi
    int my_id = syscall(SYS_gettid);

    pthread_mutex_lock(&data->mutex);

    while(data->scrittore_attivo || data->num_lett){
        data->scrittori_attesa++;
        pthread_cond_wait(&data->cv_scritt, &data->mutex);
        data->scrittori_attesa--;
    }
    data->scrittore_attivo=1;
    pthread_mutex_unlock(&data->mutex);
    
    data->value = new_value;
    printf("[%d]Scrittore: il valore scritto = %d\n",my_id,data->value);
    
    pthread_mutex_lock(&data->mutex);

    data->scrittore_attivo=0;
    if (data->scrittori_attesa){
        pthread_cond_signal(&data->cv_scritt);
    } else{
        pthread_cond_broadcast(&data->cv_lett);
    }
    pthread_mutex_unlock(&data->mutex);
    
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
    reader_param* p =  (reader_param*) par;
    
	int my_id = syscall(SYS_gettid);

    res risp;
    //TODO: Costruzione risposta con prelievo valore dalla funzione read_data
    risp.value = read_data(p->data);
    risp.sender = (long) p->sender;

    printf("READER_SERV[%d]: invio valore %d al client %ld\n",my_id,risp.value,risp.sender);

    //TODO: Invio risposta al reader client
    msgsnd(p->queue_res, (void*)&risp, sizeof(res)-sizeof(long), 0);

   // printf("READER_SERV[%d]: valore %d al client %ld INVIATO\n",my_id,risp.value,risp.sender);

    pthread_exit(NULL);
}

int main() {

    int pid;
    key_t msg_req_key = ftok(".",'a');//TODO: definire chiave
	key_t msg_res_key = ftok(".",'b'); //TODO: definire chiave

    //TODO: INIZIALIZZAZIONE CODE
    int queue_res = msgget(msg_res_key,0);
    int queue_req = msgget(msg_req_key,0);

    //TODO: inizializzazione struttura condivisa tra i thread
    data_str* d = (data_str*) malloc(sizeof(data_str));

    //TODO: inizializzazione mutex e condition variables
    d->num_lett=0;
    d->scrittore_attivo=0;
    d->scrittori_attesa=0;
    pthread_mutex_init(&d->mutex, NULL);
    pthread_cond_init(&d->cv_lett, NULL);
    pthread_cond_init(&d->cv_scritt, NULL);

    pthread_t upd, rd[NUM_READS*NUM_READERS];

    reader_param p[NUM_READS*NUM_READERS];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    srand(time(NULL));
    
    //TODO: creazione thread updater
    pthread_create(&upd, &attr, updater, (void*)d);

    req msg;
    int i;
    for (i = 0; i < NUM_READS*NUM_READERS; i++) {
        //TODO: ricezione messaggio di richiesta
        msgrcv(queue_req, (void*)&msg, sizeof(req)-sizeof(long), 0, 0);
        printf("READER:SERV: ricevuta richiesta di lettura da: %d\n",msg.pid);
        //TODO: preparazione parametro p[i]
        p[i].queue_res = queue_res;
        p[i].sender = msg.pid;
        p[i].data = d;
        //TODO: creazione thread reader
        pthread_create(&rd[i], &attr, reader, (void*)&p[i]);
    }
    //TODO: join dei thread
    for (i = 0; i < NUM_READS*NUM_READERS; i++) {
        pthread_join(rd[i], NULL);
    }
    pthread_join(upd, NULL);
    

    //TODO: deallocazione memoria e rimozione coda
    pthread_mutex_destroy(&d->mutex);
    pthread_cond_destroy(&d->cv_lett);
    pthread_cond_destroy(&d->cv_scritt);

    free(d);

    msgctl(queue_req, IPC_RMID, 0);
    msgctl(queue_res, IPC_RMID, 0);

    return 0;
}
