#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include "header.h"

static void die(const char * msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* TODO: 1. Controllare che siano passati esattamente 2 caratteri     */
    /*          es.: ./main a b                                            */
    if (argc != 3 ) die("Errore argomenti main");

    /* TODO: 2. Ricavare i due char (tx_char, rx_char) dai parametri      */
    // argv[0] è il programma. argv[1] è il puntatore a char, a noi serve il primo carattere di quella stringa
    char tx_char = argv[1][0];
    char rx_char = argv[2][0];

    /* TODO: 3. Creare (o aprire) le DUE code con open_queue(..., IPC_CREAT) */
    key_t ktx = ftok(FTOK_PATH, tx_char);
    key_t krx = ftok(FTOK_PATH, rx_char);
    if (krx <0 || ktx<0) die("Errore ftok");

    int qid_tx = msgget(ktx, IPC_CREAT|0664);
    int qid_rx = msgget(krx, IPC_CREAT|0664);

    if (qid_rx <0 || qid_tx<0) die("Errore msgget");

    printf("[PARENT] avviato - TX='%c' RX='%c'\n", tx_char, rx_char);


    /* TODO: 4. fork()  →  figlio-1  ➜  execl("./sender",  ...)           */
    /*          (passare i due char come argomenti)                       */

    pid_t pid = fork();
    if(pid<0) die("Errore fork");
    if (pid==0){
        execl("./sender", "./sender", argv[1], argv[2], (char*)NULL);
        die("Errore exec S");
    }

    /* TODO: 5. fork()  →  figlio-2  ➜  execl("./receiver", ...)         */
    pid= fork();
    if (pid==0){
        execl("./receiver", "./receiver", argv[1], argv[2], (char*)NULL);
        die("Errore exec R");
    }

    /* TODO: 6. Processo padre: wait() finché entrambi i figli terminano   */
    for (int i=0; i<2;i++) wait(NULL);

    /* TODO: 7. Rimuovere le code (msgctl IPC_RMID) se non più usate       */
    msgctl(qid_rx, IPC_RMID, 0);
    msgctl(qid_tx, IPC_RMID, 0);

    return 0;
}