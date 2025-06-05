#include "header.h"
#include "monitor_signal_continue.h"

void inizializza_monitor(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
    ls->totale_regali=0;
    ls->num_scrittori=0;
    ls->num_lettori=0;
    init_monitor(&ls->m, 2);
}

void distruggi_monitor(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
    remove_monitor(&ls->m);
}

void inizio_lettura(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
    enter_monitor(&ls->m);

    while(ls->num_scrittori>0){
        wait_condition(&ls->m, CV_LET);
    }
    ls->num_lettori++;

    leave_monitor(&ls->m);
}

void fine_lettura(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */

    enter_monitor(&ls->m);

    ls->num_lettori--;

    if (ls->num_lettori==0){
        signal_condition(&ls->m, CV_SCR);
    }

    leave_monitor(&ls->m);
}

void inizio_scrittura(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
    enter_monitor(&ls->m);

    while(ls->num_lettori>0 || ls->num_scrittori>0){
        wait_condition(&ls->m, CV_SCR);
    }
    ls->num_scrittori++;

    leave_monitor(&ls->m);
}

void fine_scrittura(MonitorLettScritt *ls) {
	/*
        TODO: completare
    */
    enter_monitor(&ls->m);

    ls->num_scrittori--;

    if (queue_condition(&ls->m, CV_SCR)){
        signal_condition(&ls->m, CV_SCR);
    } else {
        signal_all(&ls->m, CV_LET);
    }
    leave_monitor(&ls->m);
}

void Lettore(int codaresp, MonitorLettScritt *ls) {

	/*
        TODO: completare
    */
    inizio_lettura(ls);

    printf("[Lettore] Il totale regali richiesti finora è: %d\n", ls->totale_regali);

    fine_lettura(ls);
    /*
        TODO: invio messaggio conferma di ricezione 
    */
    MessaggioRisposta m;
    m.tipo=1;
    msgsnd(codaresp, (void*)&m, sizeof(MessaggioRisposta)-sizeof(long), 0);

    printf("[Lettore] Ho inviato la conferma di ricezione\n");

}

void Scrittore(int codareq, MonitorLettScritt *ls) {
    /*
        TODO: attesa messaggio
    */
    MessaggioRichiesta m;

    msgrcv(codareq, (void*)&m, sizeof(MessaggioRichiesta)-sizeof(long), 0, 0);

    printf("[Scrittore %d] Ricevuta richiesta per %d regali\n", getpid(), m.numero_regali);

	/*
        TODO: completare scrittura
    */
    inizio_scrittura(ls);

    ls->totale_regali += m.numero_regali;

    printf("[Scrittore %d] Adesso il totale dei regali richiesti è: %d\n",getpid(), ls->totale_regali);

    fine_scrittura(ls);

}
