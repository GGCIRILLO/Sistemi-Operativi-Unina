#include "header.h"
#include "monitor_signal_continue.h"

void inizializza_monitor(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
}

void distruggi_monitor(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
}

void inizio_lettura(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
}

void fine_lettura(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
}

void inizio_scrittura(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
}

void fine_scrittura(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
}

void Lettore(int codaresp, MonitorLettScritt *ls) {

	/*
        TODO: completare
    */

    printf("[Lettore] Il totale regali richiesti finora è: %d\n", ls->totale_regali);


    /*
        TODO: invio messaggio conferma di ricezione 
    */

    printf("[Lettore] Ho inviato la conferma di ricezione\n");
}

void Scrittore(int codareq, MonitorLettScritt *ls) {
    /*
        TODO: attesa messaggio
    */

	/*
        TODO: completare scrittura
    */

    printf("[Scrittore %d] Adesso il totale dei regali richiesti è: %d\n",getpid(), ls->totale_regali);

}
