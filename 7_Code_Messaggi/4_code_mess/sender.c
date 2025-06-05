#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    /* TODO: 2. Aprire la coda-TX con open_queue(tx_char, 0)               */
    /*         Aprire la coda-RX con open_queue(rx_char, 0)  (serve
               solo per inviare MSG_EXIT alla fine).                       */
    char tx_char = argv[1][0];
    char rx_char = argv[2][0];

    key_t ktx = ftok(FTOK_PATH, tx_char);
    key_t krx = ftok(FTOK_PATH, rx_char);
    if (krx <0 || ktx<0) die("Errore ftok");

    int qid_tx = msgget(ktx, 0);
    int qid_rx = msgget(krx, 0);

    if (qid_rx <0 || qid_tx<0) die("Errore msgget");

    /* TODO: 3. Loop:
               - leggere una riga da stdin (scanf)
               - costruire struct chat_msg con mtype = MSG_DATA
               - msgsnd() sulla coda-TX
               - se la riga == "exit\n":
                   * inviare MSG_EXIT sulla stessa coda
                   * break;                                                */
    Chat_msg m;
    char input[MAX_TEXT];

    while(1){
        if (scanf("%255s" , input)!=1) break;

        m.mtype = MSG_DATA;
        strcpy(m.text, input);

        if(msgsnd(qid_tx, &m, sizeof(Chat_msg)-sizeof(long), 0) ==-1 ) die("msgsnd DATA");

        if (strcmp(input, "exit")==0){
            m.mtype = MSG_EXIT;
            if (msgsnd(qid_tx, &m, sizeof(Chat_msg) - sizeof(long), 0) == -1) die("msgsnd EXIT");
            break;
        }
    }

    return 0;
}