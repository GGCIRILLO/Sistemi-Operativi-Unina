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
}

void produzione_buffer_singolo(MonitorBufferSingolo * b, int val) {

    /* TBD: Completare la produzione sul buffer singolo con sincronizzazione */
    

}

int consumazione_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Completare la consumazione dal buffer singolo con sincronizzazione */
	
   
    return val;
}

void remove_monitor_buffer_singolo(MonitorBufferSingolo * b) {

    /* TBD: Disattivare l'oggetto monitor */
}
