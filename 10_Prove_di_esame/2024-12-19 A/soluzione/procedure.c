#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

#include "header.h"

void inizializza_vettore(MonitorProdCons *pc) {
    /*
        TODO: completare
    */
    pc->num_liberi = DIM;
    pc->num_occupati = 0;
    for (int i=0;i<DIM;i++){
        pc->stato[i]=LIBERO;
    }
    init_monitor(&pc->m, 3);
}

void rimuovi_vettore(MonitorProdCons *pc) {
    /*
        TODO: completare
    */
    remove_monitor(&pc->m);
}

void inizializza_buffer(BufferBabbo * bb) {

	/*
        TODO: inizializzazione array di semafori necessari e inizializzazione struttura BufferBabbo
    */
    bb->buffer = 0;
    bb->semid = semget(IPC_PRIVATE, 3, IPC_CREAT|0664);

    semctl(bb->semid, MUTEX, SETVAL, 1);
    semctl(bb->semid, BABBO, SETVAL, 0);
    semctl(bb->semid, ELFI, SETVAL, 0);
}


void rimuovi_buffer(BufferBabbo * bb) {
    /*
        TODO: completare
    */
    semctl(bb->semid, 0, IPC_RMID);
}

void Produttore(MonitorProdCons *pc) {

    for (int i=0; i<TOT_GIOCATTOLI; i++) {
        if (i%2==0) {
            /*
        		TODO: completare
    		*/
            produci(pc, 1);
        } else {
            /*
        		TODO: completare
    		*/
            produci(pc, 2);
        }

        sleep(2);
    }

}

void produci(MonitorProdCons *pc, int tipo) {

    /*
        TODO: produzione con monitor e vettore di stato
    */
    enter_monitor(&pc->m);

    while(pc->num_liberi==0){
        wait_condition(&pc->m, CV_PROD);
    }

    int i=0;
    while(i<DIM && pc->stato[i]!=LIBERO) i++;

    pc->stato[i] = IN_USO;
    pc->num_liberi--;

    leave_monitor(&pc->m);

    sleep(1);
	/*
        TODO: completare
    */
    pc->buffer[i] = tipo;

	printf("Produzione - posizione %d, giocattolo %d\n", i, tipo);

    enter_monitor(&pc->m);

    pc->num_occupati++;

    if (tipo == 1) {
        /*
        	TODO: completare
    	*/
        pc->stato[i]=OCC_GIOCO1;
        signal_condition(&pc->m, CV_CONS1);

    } else if (tipo == 2) {
        /*
        	TODO: completare
    	*/
        pc->stato[i]=OCC_GIOCO2;
        signal_condition(&pc->m, CV_CONS2);
    }

    leave_monitor(&pc->m);

}

void Consumatore1(MonitorProdCons *pc, BufferBabbo *bb) {

    int gioco;

	/*
        TODO: consumo con monitor e vettore di stato
    */
    for (int j=0;j<10;j++){
        enter_monitor(&pc->m);

        while(pc->num_occupati==0){
            wait_condition(&pc->m, CV_CONS1);
        }

        int i=0;
        while(i<DIM && pc->stato[i]!=OCC_GIOCO1) i++;

        pc->stato[i]=IN_USO;
        pc->num_occupati--;

        leave_monitor(&pc->m);

        gioco = pc->buffer[i];

        printf("Consumo - posizione %d, gioco %d\n", i, gioco);

        /*
            TODO: consumo con monitor e vettore di stato
        */

        enter_monitor(&pc->m);

        pc->stato[i]=LIBERO;
        pc->num_liberi++;

        signal_condition(&pc->m, CV_PROD);

        leave_monitor(&pc->m);


        /*
            TODO: produzione di un aggiornamento del buffer in mutua esclusione
        */
        Wait_Sem(bb->semid, MUTEX);

        
        printf("Elfo Assemblatore 1, incremento il buffer\n");

        bb->buffer++;

        Signal_Sem(bb->semid, BABBO);

        Wait_Sem(bb->semid, ELFI);

        Signal_Sem(bb->semid, MUTEX);
    }
}

void Consumatore2(MonitorProdCons *pc, BufferBabbo *bb) {
    int gioco;

	/*
        TODO: consumo con monitor e vettore di stato
    */
    for (int j=0;j<10;j++){
            enter_monitor(&pc->m);

        while(pc->num_occupati==0){
            wait_condition(&pc->m, CV_CONS2);
        }

        int i=0;
        while(i<DIM && pc->stato[i]!=OCC_GIOCO2) i++;

        pc->stato[i]=IN_USO;
        pc->num_occupati--;

        leave_monitor(&pc->m);

        gioco = pc->buffer[i];

        printf("Consumo - posizione %d, gioco %d\n", i, gioco);

        /*
            TODO: consumo con monitor e vettore di stato
        */
        enter_monitor(&pc->m);

        pc->stato[i]=LIBERO;
        pc->num_liberi++;

        signal_condition(&pc->m, CV_PROD);

        leave_monitor(&pc->m);




        /*
            TODO: produzione di un aggiornamento del buffer in mutua esclusione
        */

        Wait_Sem(bb->semid, MUTEX);
        
        printf("Elfo Assemblatore 2, incremento il buffer\n");

        bb->buffer++;

        Signal_Sem(bb->semid, BABBO);

        Wait_Sem(bb->semid, ELFI);

        Signal_Sem(bb->semid, MUTEX);
    }
}

void BabboNatale(BufferBabbo *bb) {

	/*
        TODO: consumo di un aggiornamento del buffer in mutua esclusione
    */
    for (int i=0;i<TOT_GIOCATTOLI;i++){
        Wait_Sem(bb->semid, BABBO);

        printf("Sono Babbo Natale, ho consegnato un totale di %d regali\n",bb->buffer);

        Signal_Sem(bb->semid, ELFI);

    }
}