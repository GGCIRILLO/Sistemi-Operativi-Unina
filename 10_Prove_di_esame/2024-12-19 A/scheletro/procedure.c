#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

#include "header.h"

void inizializza_vettore(MonitorProdCons *pc) {
    /*
        TODO: completare
    */
}

void rimuovi_vettore(MonitorProdCons *pc) {
    /*
        TODO: completare
    */
}

void inizializza_buffer(BufferBabbo * bb) {

	/*
        TODO: inizializzazione array di semafori necessari e inizializzazione struttura BufferBabbo
    */
}


void rimuovi_buffer(BufferBabbo * bb) {
    /*
        TODO: completare
    */
}

void Produttore(MonitorProdCons *pc) {

    for (int i=0; i<TOT_GIOCATTOLI; i++) {
        if (i%2==0) {
            /*
        		TODO: completare
    		*/
        } else {
            /*
        		TODO: completare
    		*/
        }

		sleep(2);
    }

}

void produci(MonitorProdCons *pc, int tipo) {

    /*
        TODO: produzione con monitor e vettore di stato
    */

	sleep(1);

	/*
        TODO: completare
    */

	printf("Produzione - posizione %d, giocattolo %d\n", i, tipo);


    if (tipo == 1) {
        /*
        	TODO: completare
    	*/
    } else if (tipo == 2) {
        /*
        	TODO: completare
    	*/
    }

}

void Consumatore1(MonitorProdCons *pc, BufferBabbo *bb) {

    int gioco;

	/*
        TODO: consumo con monitor e vettore di stato
    */
	printf("Consumo - posizione %d, gioco %d\n", i, gioco);

	/*
        TODO: consumo con monitor e vettore di stato
    */




    /*
        TODO: produzione di un aggiornamento del buffer in mutua esclusione
    */
    
	printf("Elfo Assemblatore 1, incremento il buffer\n");
}

void Consumatore2(MonitorProdCons *pc, BufferBabbo *bb) {
    int gioco;

	/*
        TODO: consumo con monitor e vettore di stato
    */
	printf("Consumo - posizione %d, gioco %d\n", i, gioco);

	/*
        TODO: consumo con monitor e vettore di stato
    */




    /*
        TODO: produzione di un aggiornamento del buffer in mutua esclusione
    */
    
	printf("Elfo Assemblatore 2, incremento il buffer\n");
}

void BabboNatale(BufferBabbo *bb) {

	/*
        TODO: consumo di un aggiornamento del buffer in mutua esclusione
    */

    printf("Sono Babbo Natale, ho consegnato un totale di %d regali\n",bb->buffer);

}