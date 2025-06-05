#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "header.h"

void ProcessoP1(/* TBD: Completare il passaggio dei parametri */);
void ProcessoP2(/* TBD: Completare il passaggio dei parametri */);
void ProcessoP3(/* TBD: Completare il passaggio dei parametri */);
void ProcessoP4(/* TBD: Completare il passaggio dei parametri */);

int main() {

    srand(getpid());


    VettoreInput * input = /* TBD: Allocare e inizializzare il vettore di input */



    VettoreIntermedio * intermedio = /* TBD: Allocare e inizializzare il vettore di risultati intermedio */



    MatriceParametri1 matrice_1;

    printf("Matrice 1: \n");

    for(int i=0; i<DIM3; i++) {

        for(int j=0; j<DIM4; j++) {

            matrice_1[i][j] = rand() % 10;

            printf("[%d][%d]=%d ", i, j, matrice_1[i][j]);
        }

        printf("\n");
    }

    printf("\n");



    MatriceParametri2 matrice_2;

    printf("Matrice 2: \n");

    for(int i=0; i<DIM6; i++) {

        for(int j=0; j<DIM7; j++) {

            matrice_2[i][j] = rand() % 10;

            printf("[%d][%d]=%d ", i, j, matrice_2[i][j]);
        }

        printf("\n");

    }

    printf("\n");



    /* TBD: Avviare i processi P1, P2, P3, P4 */


    /* TBD: Attendere la terminazione dei processi P1, P2, P3, P4 */


    /* TBD: De-inizializzare e deallocare i vettori */


}


void ProcessoP1(/* TBD: Completare il passaggio dei parametri */) {

    for(int i=0; i<3; i++) {

        printf("[P1] Inserimento vettore input: ");

        int val[DIM1];

        for(int j=0; j<DIM1; j++) {

            val[j] = rand() % 10;

            printf("[%d]=%d ", j, val[j]);
        }

        printf("\n");

        inserisci_input_primo_vettore(/* TBD: Completare il passaggio dei parametri */);

        sleep(1);
    }

}

void ProcessoP2(/* TBD: Completare il passaggio dei parametri */) {

    for(int i=0; i<3; i++) {

        printf("[P2] Inserimento vettore input: ");

        int val[DIM2];

        for(int j=0; j<DIM2; j++) {

            val[j] = rand() % 10;

            printf("[%d]=%d ", DIM1+j, val[j]);
        }

        printf("\n");

        inserisci_input_secondo_vettore(/* TBD: Completare il passaggio dei parametri */);

        sleep(1);
    }
}

void ProcessoP3(/* TBD: Completare il passaggio dei parametri */) {

    for(int i=0; i<3; i++) {

        int val[DIM1+DIM2];

        preleva_input(/* TBD: Completare il passaggio dei parametri */);

        printf("[P3] Prelevamento vettore input: ");

        for(int j=0; j<DIM1+DIM2; j++) {

            printf("[%d]=%d ", j, val[j]);
        }

        printf("\n");



        int risultato[DIM5];

        for(int i=0; i<DIM3; i++) {

            risultato[i] = prodotto_scalare(/* TBD: Completare il passaggio dei parametri */);
        
        }


        printf("[P3] Inserimento vettore intermedio: ");

        for(int j=0; j<DIM5; j++) {

            printf("[%d]=%d ", j, risultato[j]);
        }

        printf("\n");

        inserisci_intermedio_vettore(/* TBD: Completare il passaggio dei parametri */);

        sleep(1);
    }

}

void ProcessoP4(VettoreIntermedio * intermedio, MatriceParametri2 matrice_2) {

    for(int i=0; i<3; i++) {

        int val[DIM5];

        preleva_intermedio(intermedio, val);

        printf("[P4] Prelevamento vettore intermedio: ");

        for(int j=0; j<DIM5; j++) {

            printf("[%d]=%d ", j, val[j]);
        }

        printf("\n");


        Output risultato;

        for(int i=0; i<DIM6; i++) {

            risultato[i] = prodotto_scalare(val, matrice_2[i], DIM7);
        
        }



        printf("[P4] Risultato: ");

        for(int j=0; j<DIM8; j++) {

            printf("[%d]=%d ", j, risultato[j]);
        }

        printf("\n");

    }


}

