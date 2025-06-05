#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "prodcons.h"

void inizializza(MonitorPC * m) {

    printf("Inizializzazione monitor\n");

    /* TBD: Inizializzazione */


	printf("Monitor inizializzato!\n");
}


void rimuovi(MonitorPC * m) {

    printf("Rimozione monitor\n");

    /* TBD: Rimozione */
}


void produci_tipo_1(MonitorPC * m, int valore) {

    int index = 0;
    int my_id = syscall(SYS_gettid);


    /* TBD: Sincronizzazione, e selezione dell'indice su cui produrre */


	
    //printf("[%d]Produttore1: Uscito da monitor\n",my_id);
 	
 	
	
    //printf("[%d]Produzione di tipo 1 in corso (valore=%d, index=%d)\n", my_id, valore, index);


	printf("[%d]Produzione di tipo 1 (valore=%d, index=%d)\n", my_id, valore, index);
	
    
    //printf("[%d]Uscito da monitor\n",my_id);
	
}


void produci_tipo_2(MonitorPC * m, int valore) {

    int index = 0;
    int my_id = syscall(SYS_gettid);


    /* TBD: Sincronizzazione, e selezione dell'indice su cui produrre */
    
    //printf("[%d]Produttore2: Uscito da monitor\n",my_id);


   // printf("[%d]Produzione di tipo 2 in corso (valore=%d, index=%d)\n", my_id,valore, index);

    
	//printf("[%d]Uscito da monitor\n",my_id);
}


void consuma_tipo_1(MonitorPC * m, int * valore) {

    int index = 0;
	int my_id = syscall(SYS_gettid);

    /* TBD: Sincronizzazione, e selezione dell'indice su cui consumare */
    
	
    //printf("[%d]Consumatore1: Uscito da monitor\n",my_id);

    
    printf("[%d]Consumazione di tipo 1 (valore=%d, index=%d)\n", my_id,*valore, index);
    
    
	//printf("[%d]Uscito da monitor\n",my_id);
}


void consuma_tipo_2(MonitorPC * m, int * valore) {

    int index = 0;
	int my_id = syscall(SYS_gettid);

    /* TBD: Sincronizzazione, e selezione dell'indice su cui consumare */
    
	
    //printf("[%d]Consumatore2: Uscito da monitor\n",my_id);

    

    printf("[%d]Consumazione di tipo 2 (valore=%d, index=%d)\n",my_id, *valore, index);
    
	
    //printf("[%d]Uscito da monitor\n",my_id);
}
