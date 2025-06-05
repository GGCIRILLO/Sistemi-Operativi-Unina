			/*----IMPLEMENTAZIONE DELLE PROCEDURE----*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "semafori.h"
#include <math.h>

void produci_tipo_1(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 1

	printf("[Produttore %d] ho prodotto %d di tipo 1, in posizione %d\n", getpid(), value, index);
	

}

void produci_tipo_2(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 2 

	printf("[Produttore %d] ho prodotto %d di tipo 2, in posizione %d\n", getpid(), value, index);

}

void consuma_tipo_1(BufferMutuaEx * buf, int semid) {

	// TODO: completare consumo 1
	
	printf("[Consumatore %d] consumo elemento %d di tipo 1 in posizione %d\n",getpid(), value, index);	

}

void consuma_tipo_2(BufferMutuaEx * buf, int semid) {
	
	// TODO: completare consumo 2

	printf("[Consumatore %d] consumo elemento %d di tipo 2 in posizione %d\n",getpid(), value, index);	

}
