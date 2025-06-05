#include "prodcons.h"

#include <stdio.h>


void inizializza(MonitorStreaming * m) {

    /* TBD: Inizializzare il monitor */
}

void produci(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */

    printf("Produzione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);

    /* TBD */ = f[0][0];
    /* TBD */ = f[0][1];
    /* TBD */ = f[1][0];
    /* TBD */ = f[1][1];

}

void consuma(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */

    f[0][0] = /* TBD */
    f[0][1] = /* TBD */
    f[1][0] = /* TBD */
    f[1][1] = /* TBD */

    printf("Consumazione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);

}

void bufferizza(MonitorStreaming * m, int n) {

    /* TBD: Completare il metodo */

}

void distruggi(MonitorStreaming * m) {

    /* TBD: Completare il metodo */
}