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
	Wait_Sem(semid, SPAZIO);

	Wait_Sem(semid, MUTEXP);

	int index=0;
	while(index<DIM && buf->stato[index]!=LIBERO) index++;

	if (index<DIM) buf->stato[index]=IN_USO;

	Signal_Sem(semid, MUTEXP);

	int n = rand()%2+1;
	sleep(n);

	buf->buffer[index] = value;

	printf("[Produttore %d] ho prodotto %d di tipo 1, in posizione %d\n", getpid(), value, index);

	buf->stato[index] = OCC_TIPO1;

	Signal_Sem(semid, MESSAGGIO);
	
}

void produci_tipo_2(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 2
	Wait_Sem(semid, SPAZIO);

	Wait_Sem(semid, MUTEXP);

	int index=0;
	while(index<DIM && buf->stato[index]!=LIBERO) index++;

	if (index<DIM) buf->stato[index]=IN_USO;

	Signal_Sem(semid, MUTEXP);

	int n = rand()%2+1;
	sleep(n);

	buf->buffer[index] = value; 

	printf("[Produttore %d] ho prodotto %d di tipo 2, in posizione %d\n", getpid(), value, index);

	buf->stato[index] = OCC_TIPO2;

	Signal_Sem(semid, MESSAGGIO);

}

void consuma_tipo_1(BufferMutuaEx * buf, int semid) {

	// TODO: completare consumo 1
	int index=0;
	int value;

	Wait_Sem(semid, MESSAGGIO);

	Wait_Sem(semid, MUTEXC);

	while (index<DIM && buf->stato[index]!=OCC_TIPO1) index++;

	if (index<DIM) buf->stato[index] = IN_USO; 

	Signal_Sem(semid, MUTEXC);

	int n = rand()%2+1;
	sleep(n);

	value = buf->buffer[index];
	
	printf("[Consumatore %d] consumo elemento %d di tipo 1 in posizione %d\n",getpid(), value, index);	

	buf->stato[index] = LIBERO; 

	Signal_Sem(semid, SPAZIO);

}

void consuma_tipo_2(BufferMutuaEx * buf, int semid) {
	
	// TODO: completare consumo 2
	int index=0;
	int value;

	Wait_Sem(semid, MESSAGGIO);

	Wait_Sem(semid, MUTEXC);

	while (index<DIM && buf->stato[index]!=OCC_TIPO2) index++;

	if (index<DIM) buf->stato[index] = IN_USO; 

	Signal_Sem(semid, MUTEXC);

	int n = rand()%2+1;
	sleep(n);

	value = buf->buffer[index];

	printf("[Consumatore %d] consumo elemento %d di tipo 2 in posizione %d\n",getpid(), value, index);	

	
	buf->stato[index] = LIBERO; 

	Signal_Sem(semid, SPAZIO);

}
