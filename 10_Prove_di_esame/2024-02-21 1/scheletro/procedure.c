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
}

void init_intermedio(VettoreIntermedio *v) {

    /* TBD: Completare l'inizializzazione */
}

void remove_input(VettoreInput *v) {

    /* TBD: Completare la de-inizializzazione */
}

void remove_intermedio(VettoreIntermedio *v) {

    /* TBD: Completare la de-inizializzazione */
}

void inserisci_input_primo_vettore(VettoreInput *v, int *val) {

    /* TBD: Completare la sincronizzazione */

    for(int i=0; i<DIM1; i++) {

        v->primo_vettore[i] = val[i];
    }

}

void inserisci_input_secondo_vettore(VettoreInput *v, int *val) {

    /* TBD: Completare la sincronizzazione */

    for(int i=0; i<DIM2; i++) {

        v->secondo_vettore[i] = val[i];
    }

}

void preleva_input(VettoreInput *v, int *val) {

    /* TBD: Completare la sincronizzazione */

    for(int i=0; i<DIM1; i++) {

        val[i] = v->primo_vettore[i];
    }

    for(int i=0; i<DIM2; i++) {

        val[i+DIM1] = v->secondo_vettore[i];
    }

}

void inserisci_intermedio_vettore(VettoreIntermedio *v, int *val) {

    /* TBD: Completare la sincronizzazione */

    for(int i=0; i<DIM5; i++) {

        v->vettore[i] = val[i];
    }

}

void preleva_intermedio(VettoreIntermedio *v, int *val) {

    /* TBD: Completare la sincronizzazione */

    for(int i=0; i<DIM5; i++) {

        val[i] = v->vettore[i];
    }

}

