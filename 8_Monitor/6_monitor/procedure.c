#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "header.h"

void InizioLettura(Monitor* M, Buffer * buf){
	
	/* TBD: Effettuare inizio lettura */
    enter_monitor(M);

    printf("Inizio lettura\n");

    if(buf->num_scrittori>0){
        printf("Sospensione lettura per Scrittori in corso...\n");
        wait_condition(M, SYNCHL);
        printf("Ripresa lettura\n");
    }
    buf->num_lettori++;
    printf("Num Lettori: %d\n", buf->num_lettori);
    signal_condition(M, SYNCHL);
    leave_monitor(M);

}

void FineLettura(Monitor* M, Buffer * buf) {

	/* TBD: Effettuare fine lettura */
    enter_monitor(M);
    buf->num_lettori--;
    if(buf->num_lettori==0){
        printf("Fine Lettura - Signal Scrittori\n");
        signal_condition(M, SYNCHS);
    }
    leave_monitor(M);
    printf("Uscita Monitor Lettura...\n");

} 

//Procedure di inizio e fine scrittura

void InizioScrittura(Monitor* M,Buffer*buf){

	/* TBD: Effettuare inizio scrittura */
    enter_monitor(M);

    printf("Inizio Scrittura\n");

    if (buf->num_lettori>0 || buf->num_scrittori>0){
        printf("Sospensione Scrittura...\n");
        wait_condition(M, SYNCHS);
        printf("Ripresa Scrittura...\n");
    }
    buf->num_scrittori++;
    leave_monitor(M);
}

void FineScrittura(Monitor* M, Buffer*buf){

	/* TBD: Effettuare inizio scrittura */
    enter_monitor(M);
    buf->num_scrittori--;
    if(queue_condition(M, SYNCHS)){
        printf("Altri scittori in attesa...Attivazione scrittore\n");
        signal_condition(M, SYNCHS); 
    } else{
        printf("Fine scittura... Attivo lettori\n");
        signal_condition(M, SYNCHL);
    }
    leave_monitor(M);
    printf("Uscita Monitor Scrittura\n");
}

void Servizio(Monitor* M, Buffer * buf){

	srand(time(0));

	int i;
	for(i=0; i<5; i++) {

		/* TBD: Richiamare InizioScrittura e FineScrittura */
        InizioScrittura(M, buf);

		buf->meteo.temperatura = (rand()%101)-50;
		buf->meteo.umidita = rand()%101;
		buf->meteo.pioggia = rand()%2;

		printf("<%d> scrittura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );

		sleep(2);

        FineScrittura(M, buf);
	}

}

void Utente(Monitor* M, Buffer * buf) {

	int i;
	for(i=0; i<5; i++) {
		
		/* TBD: Richiamare InizioLettura e FineLettura */
        InizioLettura(M, buf);

		printf("<%d> lettura: Temperatura=%d, Umidità=%d, Pioggia=%s\n", getpid(), buf->meteo.temperatura, buf->meteo.umidita, (buf->meteo.pioggia ? "si" : "no") );

		sleep(1);

        FineLettura(M, buf);
	}

}