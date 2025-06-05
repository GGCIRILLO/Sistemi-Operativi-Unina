#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void * thread_lettore(void *);
void * thread_scrittore(void *);

// Variabile globale
int id_coda_sensore;

int lettura(MonitorLS * m) {

    /* 
        NOTA: C'è un unico scrittore
    */
    int my_id = syscall(SYS_gettid);
    pthread_mutex_lock(&m->mutex);

    while(m->scrittura>0){
        printf("[%d]Sospensione lettore\n",my_id);
    	pthread_cond_wait(&m->cv_synch,&m->mutex);
    	printf("[%d]Riattivazione lettore\n",my_id);
    }
    m->num_lettori++;
    pthread_mutex_unlock(&m->mutex);    
     
    int val;
    val = m->valore;
    printf("[%d]Lettore: il valore letto = %d\n",my_id,val);

    // TODO: completare lettura
    pthread_mutex_lock(&m->mutex);
    m->num_lettori--;
    if (m->num_lettori==0){
        pthread_cond_signal(&m->cv_synch);
    }
    pthread_mutex_unlock(&m->mutex);
        
    return val;
}

void scrittura(MonitorLS * m, int valore) {
    
    /* 
        NOTA: C'è un unico scrittore
    */
    int my_id = syscall(SYS_gettid);
    pthread_mutex_lock(&m->mutex);

    while(m->num_lettori>0){
        printf("[%d]Sospensione scrittore\n",my_id);
    	pthread_cond_wait(&m->cv_synch,&m->mutex);
    	printf("[%d]Riattivazione scrittore\n",my_id);
    }
    m->scrittura = 1;

    pthread_mutex_unlock(&m->mutex);

    // TODO: completare scrittura
    m->valore = valore;
    printf("[%d]Scrittore: il valore scritto = %d\n",my_id,m->valore);

    pthread_mutex_lock(&m->mutex);

    m->scrittura = 0;

    pthread_cond_broadcast(&m->cv_synch);

    pthread_mutex_unlock(&m->mutex);
}

void main() {

	srand(time(NULL));

	int key_coda = ftok(FTOK_PATH, FTOK_CHAR);// TODO
    if (key_coda<0) die("ftok");

    int id_coda_sensore = msgget(key_coda, 0); //TODO
    if (id_coda_sensore<0) die("msgget");

    printf("Avvio processo smistatore...\n");

    pthread_t scrittore;
    pthread_t lettori[LETTORI];

    MonitorLS * m = malloc(sizeof(MonitorLS));//TODO

    // TODO: inizializzare variabili per la mutua esclusione
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cv_synch, NULL);
    m->num_lettori = 0;
    m->scrittura = 0;

    // TODO: creare thread scrittore
    pthread_create(&scrittore, NULL, thread_scrittore, (void*)m);
    
    for(int i=0; i<3; i++) {
    	// TODO: creare thread lettori
        pthread_create(&lettori[i], NULL, thread_lettore, (void*)m);
    }

    // TODO: attendere la terminazione dei thread
    pthread_join(scrittore, NULL);
    for (int i=0;i<3;i++){
        pthread_join(lettori[i], NULL);
    }

	// TODO: deallocare la struttura
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->cv_synch);
	free(m);
}

void * thread_lettore(void * x) {

    MonitorLS * ls = (MonitorLS*)x; //TODO: recupero parametri

    for(int i=0; i<10; i++) {

        sleep(1);

        // TODO: leggere il valore, moltiplicarlo per un intero tra 1 e 100 e stamparlo a video
        int valore_old = lettura(ls);
        int valore = valore_old*(rand()%100+1);
        
        printf("Lettore: Stampo valore originale = %d e valore finale = %d\n", valore_old, valore);
    }

    pthread_exit(NULL);
}

void * thread_scrittore(void * x) {

    MonitorLS * ls = (MonitorLS*)x; // TODO: recupero parametri

    for(int i=0; i<10; i++) {

        printf("Smistatore: In attesa di messaggi...\n");

        // TODO: ricezione messaggio
        Messaggio m;
        int ret = msgrcv(id_coda_sensore, (void*)&m, sizeof(m)-sizeof(long), TIPO, 0);
        if (ret<0) die("msgrcv");
                
        printf("Scrittore: Ricevuto valore = %d\n", m.valore);

        // TODO: scrivere il messaggio nel monitor
        scrittura(ls, m.valore);
    }

    pthread_exit(NULL);
}
