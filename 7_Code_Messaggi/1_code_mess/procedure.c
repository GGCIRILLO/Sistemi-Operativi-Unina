/******** IMPLEMENTAZIONE FUNZIONI (procedure.c) ***************/
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>
#include "header.h"

/*---------------- PRODUTTORE ----------------*/
void Produttore(int queue, char *text) {
    Messaggio m;
    m.tipo = MESSAGGIO;            /* SET DEL TIPO (costante 1)   */
    strcpy(m.mess, text);          /* COPIA IL PAYLOAD            */

    if (msgsnd(queue, &m, sizeof(Messaggio) - sizeof(long), IPC_NOWAIT) == -1)
        perror("msgsnd");          /* N.B.  IPC_NOWAIT → non blocca se coda piena */

    printf("[SEND] <%s>\n", m.mess);
}

/*---------------- CONSUMATORE ---------------*/
void Consumatore(int queue) {
    Messaggio m;

    if (msgrcv(queue, &m, sizeof(Messaggio) - sizeof(long),
               MESSAGGIO, 0) == -1)             /* 0 = RICEZIONE BLOCCANTE   */
    {
        perror("msgrcv");
        return;
    }

    printf("[RECV] <%s>\n", m.mess);
    printMsgInfo(queue);           /* STATO ATTUALE DELLA CODA    */
}

/*-------- STAMPA METADATI CODA --------------*/
void printMsgInfo(int queue) {
    struct msqid_ds info;
    if (msgctl(queue, IPC_STAT, &info) == -1) {
        perror("msgctl"); return;
    }

    printf("  msg_qnum = %lu |", info.msg_qnum);           /* MESSAGGI IN CODA */

    /* ctime() aggiunge '\n' → niente newline espliciti qui */
    printf("  last send: %s",    ctime(&info.msg_stime));
    printf("  last recv: %s",    ctime(&info.msg_rtime));
    printf("  last ctrl: %s",    ctime(&info.msg_ctime));
}
/***************************************************************/