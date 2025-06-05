#include <stdio.h>

#include "prodcons.h"


void init_monitor_circolare(MonitorVettoreCircolare * p) {

    /* TBD: Inizializzare il monitor */
}

void produzione_circolare(MonitorVettoreCircolare * p, int val) {

    /* TBD: Completare la produzione nel buffer circolare con sincronizzazione */

    p->buffer[/* TBD */] = val;


int consumazione_circolare(MonitorVettoreCircolare * p) {

    /* TBD: Completare la consumazione dal buffer circolare con sincronizzazione */

    int val;

    val = p->buffer[/* TBD */];

    return val;
}

void remove_monitor_circolare(MonitorVettoreCircolare * p) {

    /* TBD: Disattivare l'oggetto monitor */
}



void init_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Inizializzare il monitor */
}

void produzione_buffer_singolo(MonitorBufferSingolo * b, int val) {

    /* TBD: Completare la produzione sul buffer singolo con sincronizzazione */

    b->buffer = val;

}

int consumazione_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Completare la consumazione dal buffer singolo con sincronizzazione */

    int val;

    val = b->buffer;

    return val;
}

void remove_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Disattivare l'oggetto monitor */
}
