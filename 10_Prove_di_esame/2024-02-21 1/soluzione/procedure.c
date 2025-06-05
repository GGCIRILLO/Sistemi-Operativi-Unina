#include "header.h"

int prodotto_scalare(int *v1, int *v2, int n) {

    int sum = 0;

    for(int i=0; i<n; i++) {

        sum += v1[i] * v2[i];
    }

    return sum;
}



void init_input(VettoreInput *v) {

    /* TBD: Completare l'inizializzazione */
    for(int i=0; i<DIM1; i++) {

        v->primo_vettore[i] = 0;
    }
    for(int i=0; i<DIM2; i++) {

        v->secondo_vettore[i] = 0;
    }
    
    init_monitor(&v->m, 2);
}

void init_intermedio(VettoreIntermedio *v) {

    /* TBD: Completare l'inizializzazione */
    for(int i=0; i<DIM5; i++) {

        v->vettore[i] = 0;
    }
    init_monitor(&v->m, 2);
}

void remove_input(VettoreInput *v) {

    /* TBD: Completare la de-inizializzazione */
    for(int i=0; i<DIM1; i++) {

        v->primo_vettore[i] = 0;
    }
    for(int i=0; i<DIM2; i++) {

        v->secondo_vettore[i] = 0;
    }
    remove_monitor(&v->m);
}

void remove_intermedio(VettoreIntermedio *v) {

    /* TBD: Completare la de-inizializzazione */
    for(int i=0; i<DIM5; i++) {

        v->vettore[i] = 0;
    }
    remove_monitor(&v->m);
}

void inserisci_input_primo_vettore(VettoreInput *v, int *val) {

    /* TBD: Completare la sincronizzazione */
    enter_monitor(&v->m);

    if (v->ready_parts==2){
        wait_condition(&v->m, CV_FULL);
    }

    for(int i=0; i<DIM1; i++) {

        v->primo_vettore[i] = val[i];
    }

    v->ready_parts++;

    if (v->ready_parts==2){
        signal_condition(&v->m, CV_EMPTY);
    }

    leave_monitor(&v->m);

}

void inserisci_input_secondo_vettore(VettoreInput *v, int *val) {

    /* TBD: Completare la sincronizzazione */
    enter_monitor(&v->m);
    if (v->ready_parts == 2){
        wait_condition(&v->m, CV_FULL);
    }

    for(int i=0; i<DIM2; i++) {

        v->secondo_vettore[i] = val[i];
    }

    v->ready_parts++;

    if (v->ready_parts == 2){
        signal_condition(&v->m, CV_EMPTY);
    }

    leave_monitor(&v->m);
}

void preleva_input(VettoreInput *v, int *val) {

    /* TBD: Completare la sincronizzazione */
    enter_monitor(&v->m);

    if (v->ready_parts != 2){
        wait_condition(&v->m, CV_EMPTY);
    }

    for(int i=0; i<DIM1; i++) {

        val[i] = v->primo_vettore[i];
    }

    for(int i=0; i<DIM2; i++) {

        val[i+DIM1] = v->secondo_vettore[i];
    }

    v->ready_parts = 0;
    signal_condition(&v->m, CV_FULL);
    leave_monitor(&v->m);

}

void inserisci_intermedio_vettore(VettoreIntermedio *v, int *val) {

    /* TBD: Completare la sincronizzazione */
    enter_monitor(&v->m);

    if (v->ready==1){
        wait_condition(&v->m, CV_FULL);
    }

    for(int i=0; i<DIM5; i++) {

        v->vettore[i] = val[i];
    }
    v->ready = 1;

    signal_condition(&v->m, CV_EMPTY);

    leave_monitor(&v->m);

}

void preleva_intermedio(VettoreIntermedio *v, int *val) {

    /* TBD: Completare la sincronizzazione */
    enter_monitor(&v->m);

    if (v->ready==0){
        wait_condition(&v->m, CV_EMPTY);
    }

    for(int i=0; i<DIM5; i++) {

        val[i] = v->vettore[i];
    }
    v->ready=0;

    signal_condition(&v->m, CV_FULL);

    leave_monitor(&v->m);

}

