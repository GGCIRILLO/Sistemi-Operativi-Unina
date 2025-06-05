#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

void main() {

    printf("Avvio processo sensore...\n");
    
    int key_coda = ftok(FTOK_PATH, FTOK_CHAR);// TODO
    if (key_coda<0) die("ftok");

    int id_coda_sensore = msgget(key_coda, 0); //TODO
    if (id_coda_sensore<0) die("msgget");

    srand(time(NULL));

    Messaggio m;
    m.tipo = TIPO;

    for(int i=0; i<10; i++) {

        // TODO: inviare interi casuali sulla coda
        m.valore = rand() % 11;

        int ret = msgsnd(id_coda_sensore, (void*)&m, sizeof(m)-sizeof(long), 0);
        if (ret<0) die("msgsnd");
        
        printf("[%d]Messaggio inviato: %d\n",getpid(),m.valore);
        
        sleep(1);
    }

}
