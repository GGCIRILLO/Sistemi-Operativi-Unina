/* IMPLEMENTAZIONE DELLE PROCEDURE – Monitor Hoare */

#include "procedure.h"
#include <stdio.h>
#include <unistd.h>

/* ------------------------------------------------------------------ */
void w_init(Warehouse *w)
{
    /* TBD: inizializzare contatori, stati degli slot e monitor */
    w->liberi =N_SLOTS;
    w->occupati=0;
    for (int i=0;i<N_SLOTS;i++){
        w->stato[i]=LIBERO;
    }
    init_monitor(&(w->m), NUM_COND);
}

void w_remove(Warehouse *w)
{
    /* TBD: remove_monitor(&(w->m));                               */
    remove_monitor(&(w->m));
}

/* ------------------------- CLIENTI ------------------------------- */
int w_prenota(Warehouse *w)
{

    /* TBD:
       enter_monitor
       if (w->liberi <= 1) wait(CV_CLIENTI); // deve rimanere almeno uno slot libero
       trovare uno slot LIBERO → idx
       w->stato[idx] = PRENOTATO; w->liberi--;
       signal(CV_CLIENTI);          // pass-the-baton
       leave_monitor                                                    */
    enter_monitor(&(w->m));
    if (w->liberi<=1){
        printf("[CLI %d] wait: liberi=%d (deve essere ≥2)\n",
               getpid(), w->liberi);
        wait_condition(&(w->m), CV_CLIENTI);
        printf("[CLI %d] wake-up: liberi=%d\n", getpid(), w->liberi);
    }

    int i=0;
    while (i<N_SLOTS && w->stato[i]!=LIBERO) { 
        i++;
    }

    w->stato[i] = PRENOTATO;
    w->liberi--;

    printf("[CLI %d] prenotato slot %d  (liberi=%d)\n",
           getpid(), i, w->liberi);


    signal_condition(&(w->m), CV_CLIENTI);

    leave_monitor(&(w->m));


    return i;
}

void w_conferma(Warehouse *w, int idx)
{
    /* TBD:
       enter_monitor
       w->stato[idx] = OCCUPATO; w->occupati++;
       signal(CV_RIFORNITORI);
       leave_monitor                                                  */
    enter_monitor(&(w->m));

    w->stato[idx] = OCCUPATO;
    w->occupati++;

    printf("[CLI %d] OCCUPATO slot %d  (occupati=%d)\n",
           getpid(), idx, w->occupati);

    signal_condition(&(w->m), CV_RIFORNITORI);

    leave_monitor(&(w->m));
}

/* ---------------------- RIFORNITORI ------------------------------ */
int w_prenota_occupato(Warehouse *w)
{
    /* TBD:
       enter_monitor
       if (w->occupati == 0) wait(CV_RIFORNITORI);
       trovare OCCUPATO → idx
       w->stato[idx] = PRENOTATO; w->occupati--;
       leave_monitor                                                  */
    enter_monitor(&(w->m));
    if(w->occupati==0){
        printf("[RIF %d] wait: occupati=0\n", getpid());
        wait_condition(&(w->m), CV_RIFORNITORI);
        printf("[RIF %d] wake-up: occupati=%d\n", getpid(), w->occupati);
    }

    int i=0;
    while(i<N_SLOTS && w->stato[i] != OCCUPATO){
        i++;
    }
    w->stato[i] = PRENOTATO;
    w->occupati--;

    printf("[RIF %d] preso slot %d  (occupati=%d)\n",
           getpid(), i, w->occupati);

    leave_monitor(&(w->m));

    return i;
}

void w_libera(Warehouse *w, int idx)
{
    /* TBD:
       enter_monitor
       w->stato[idx] = LIBERO; w->liberi++;
       signal(CV_CLIENTI);          // sveglia un cliente se 2+ liberi
       signal(CV_RIFORNITORI)       // sveglia rif altrimenti
       leave_monitor                                                  */

    enter_monitor(&(w->m));
    w->stato[idx]= LIBERO;
    w->liberi++;

    printf("[RIF %d] LIBERO slot %d  (liberi=%d)\n",
           getpid(), idx, w->liberi);

    /* sveglia un cliente **solo se** ora ci sono ≥2 slot liberi        */
    if (w->liberi >= 2)
        signal_condition(&w->m, CV_CLIENTI);
    else                        /* altrimenti priorità a rifornitori    */
        signal_condition(&w->m, CV_RIFORNITORI);

    leave_monitor(&(w->m));
}