#include <stdio.h>

#include "prodcons.h"


void init_monitor_circolare(MonitorVettoreCircolare * p) {

    /* TBD: Inizializzare il monitor */
    p->testa=0;
    p->coda=0;
    p->count=0;
    init_monitor(&p->m, 2);
}

void produzione_circolare(MonitorVettoreCircolare * p, int val) {

    /* TBD: Completare la produzione nel buffer circolare con sincronizzazione */
    enter_monitor(&p->m);

    if(p->count==DIM){
        wait_condition(&p->m, CV_PROD);
    }
    
    p->buffer[p->testa/* TBD */] = val;
    p->testa = (p->testa+1)%DIM;
    p->count++;

    signal_condition(&p->m, CV_CONS);

    leave_monitor(&p->m);
}

int consumazione_circolare(MonitorVettoreCircolare * p) {

    /* TBD: Completare la consumazione dal buffer circolare con sincronizzazione */

    int val;

    enter_monitor(&p->m);
    
    if (p->count==0){
        wait_condition(&p->m, CV_CONS);
    }

    val = p->buffer[p->coda/* TBD */];
    p->coda = (p->coda+1)%DIM;
    p->count--;

    signal_condition(&p->m, CV_PROD);

    leave_monitor(&p->m);

    return val;
}

void remove_monitor_circolare(MonitorVettoreCircolare * p) {

    /* TBD: Disattivare l'oggetto monitor */
    remove_monitor(&p->m);
}



void init_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Inizializzare il monitor */
    init_monitor(&b->m, 2);
    b->occupato=0;
}

void produzione_buffer_singolo(MonitorBufferSingolo * b, int val) {

    /* TBD: Completare la produzione sul buffer singolo con sincronizzazione */
    enter_monitor(&b->m);

    if (b->occupato){
        wait_condition(&b->m, CV_PROD);
    }

    b->buffer = val;
    b->occupato=1;

    signal_condition(&b->m, CV_CONS);

    leave_monitor(&b->m);

}

int consumazione_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Completare la consumazione dal buffer singolo con sincronizzazione */

    int val;

    enter_monitor(&b->m);

    if (!b->occupato){
        wait_condition(&b->m, CV_CONS);
    }

    val = b->buffer;
    b->occupato=0;

    signal_condition(&b->m, CV_PROD);

    leave_monitor(&b->m);

    return val;
}

void remove_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Disattivare l'oggetto monitor */
    remove_monitor(&b->m);
}
