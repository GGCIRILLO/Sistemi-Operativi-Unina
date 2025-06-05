#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "header_msg.h"

int main() {

    key_t chiave_collettore = /*TODO*/;
    int id_queue_collettore = /*TODO*/;

    key_t chiave_server = /*TODO*/;
    int id_queue_server = /*TODO*/;

    //TODO: creazione ed eseuzione processo server

    //TODO: creazione processo collettore

    //TODO: creazione processi sensori, ciascuno con il proprio ID
    

    //TODO: attesa dei processi figli
    

    //TODO: rimozione risorse IPC
    
    return 0;
}