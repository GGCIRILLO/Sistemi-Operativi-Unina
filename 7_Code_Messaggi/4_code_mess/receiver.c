#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include "header.h"

static void die(const char * msg){
    perror(msg);
    exit(1);
}


int main(int argc, char *argv[])
{
    /* TODO: 1. Controllare argomenti (due caratteri)                      */
    if(argc!=3) die("Errore argomenti sender");

    /* TODO: 2. Aprire la coda-RX con open_queue(rx_char, 0)               */
    char rx_char = argv[2][0];

    key_t krx = ftok(FTOK_PATH, rx_char);
    if (krx <0) die("Errore ftok");

    int qid_rx = msgget(krx, 0);

    if (qid_rx <0) die("Errore msgget");
    

    /* TODO: 3. Loop:
               - msgrcv() bloccante (msgtyp = 0 per primo arrivato)
               - se mtype == MSG_EXIT  → break;
               - else stampare msg.text su stdout                          */

    Chat_msg m;
    while(1){
        if(msgrcv(qid_rx, &m, sizeof(Chat_msg)-sizeof(long), 0, 0)==-1) die("msgrcv");
        if(m.mtype==MSG_EXIT) break;
        printf("%s\n",m.text);
    }

    return 0;
}