#ifndef __HEADER
#define __HEADER

//Funzioni che ci servono
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_REQ 10

// TODO: completare il messaggio misura dai sensori
typedef struct{
	//...
	long id_client;
	int valore;
}Misura;

typedef struct{
	int somma;
	// TODO completare con le variabili per la sincronizzazione tra i thread
	int count;

	pthread_mutex_t mutex;
	pthread_cond_t cv_worker;
	pthread_cond_t cv_collector;

}Buffer;

static inline void die(const char * msg){
	perror(msg);
	exit(1);
}

#endif
