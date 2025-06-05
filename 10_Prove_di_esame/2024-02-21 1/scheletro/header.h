#ifndef _HEADER_
#define _HEADER_

#include "monitor_hoare.h"

#define DIM1 4
#define DIM2 3

#define DIM3 3
#define DIM4 7

#define DIM5 3

#define DIM6 2
#define DIM7 3

#define DIM8 2

typedef struct {

    int primo_vettore[DIM1];
    int secondo_vettore[DIM2];

    /* TBD: Definire ulteriori variabili per la sincronizzazione */

} VettoreInput;

typedef int MatriceParametri1[DIM3][DIM4];


typedef struct {

    int vettore[DIM5];

    /* TBD: Definire ulteriori variabili per la sincronizzazione */

} VettoreIntermedio;

typedef int MatriceParametri2[DIM6][DIM7];

typedef int Output[DIM8];


int prodotto_scalare(int *v1, int *v2, int n);

void init_input(VettoreInput *v);
void init_intermedio(VettoreIntermedio *v);
void remove_input(VettoreInput *v);
void remove_intermedio(VettoreIntermedio *v);

void inserisci_input_primo_vettore(VettoreInput *v, int *val);
void inserisci_input_secondo_vettore(VettoreInput *v, int *val);
void preleva_input(VettoreInput *v, int *val);

void inserisci_intermedio_vettore(VettoreIntermedio *v, int *val);
void preleva_intermedio(VettoreIntermedio *v, int *val);

#endif