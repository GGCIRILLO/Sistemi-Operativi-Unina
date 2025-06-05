#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

#include "prodcons.h"


void init_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Inizializzare il monitor */
    init_monitor(&b->m, 2);
    b->libero = 0;
}

void produzione_buffer_singolo(MonitorBufferSingolo * b, int val) {

    /* TBD: Completare la produzione sul buffer singolo con sincronizzazione */
    enter_monitor(&b->m);

    if(b->libero == 1) {
        printf("[%d] [PRODUTTORE] Sospeso buffer pieno\n", getpid());
        wait_condition(&b->m, VARCOND_PRODUTTORI);
        printf("[%d] [PRODUTTORE] Ripreso\n", getpid());
    }

    b->buffer = val;
    b->libero = 1;

    signal_condition(&b->m, VARCOND_CONSUMATORI);

    leave_monitor(&b->m);
}

int consumazione_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Completare la consumazione dal buffer singolo con sincronizzazione */
    int val;

    enter_monitor(&b->m);

    if (b->libero==0){
        printf("[%d] [CONSUMATORE] Sospeso buffer vuoto\n", getpid());
        wait_condition(&b->m, VARCOND_CONSUMATORI);
        printf("[%d] [CONSUMATORE] Ripreso\n", getpid());
    }

    val = b->buffer;
    b->libero = 0;

    signal_condition(&b->m, VARCOND_PRODUTTORI);

    leave_monitor(&b->m);
	
    return val;
}

void remove_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Disattivare l'oggetto monitor */
    remove_monitor(&b->m);
}
