#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>
#include "header.h"


static void show_time(void) {
    /* TODO: funzione di utilità che stampa hh:mm:ss                     */
    time_t now  = time(NULL);
    struct tm *lt  = localtime(&now);
    printf("%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);
}

static void die(const char *msg) { 
    perror(msg); 
    exit(1); 
}

int main(int argc, char *argv[])
{
    /* TODO 1: controllare argc, aprire coda con msgget(qid, 0)           */
    if (argc != 2) die("Errore argc centro");
    int qid = atoi(argv[1]);
    if (qid < 0)  die("qid Centro");



    /* TODO 2: contatori polizia/meteo, loop finché tot < 16              */
    /*         - primo tentativo: msgrcv con msgtyp = MSG_POLIZIA|IPC_NOWAIT
               - se non arriva, msgrcv con msgtyp = 0 (bloccante)         */
    int count_polizia = 0;
    int count_meteo = 0;
    Alert a;
    int finito_polizia = 0, finito_meteo = 0;

    while (!(finito_polizia && finito_meteo)){
        /* 1° tentativo: solo Polizia, non bloccante */
        if (msgrcv(qid, &a, sizeof a - sizeof(long),
                   MSG_POLIZIA, IPC_NOWAIT) == -1)
        {
            if (errno != ENOMSG) die("msgrcv");
            /* nessun Polizia: prendo il primo in coda (bloccante) */
            if (msgrcv(qid, &a, sizeof a - sizeof(long), 0, 0) == -1)
                die("msgrcv");
        }

        if (strcmp(a.text, "FINE") == 0) {
            if (a.mtype == MSG_POLIZIA) finito_polizia = 1;
            else                        finito_meteo   = 1;
            continue;                           /* NON incrementare contatori */
        }

        /* TODO 3: stampare per ogni allarme =>
               [CENTRO] hh:mm:ss  POLIZIA|METEO : <testo>                 */
        printf("[CENTRO] ");
        show_time();
        if (a.mtype == MSG_POLIZIA) {
            printf("  POLIZIA : %s\n", a.text);
            ++count_polizia;
        } else if (a.mtype == MSG_METEO) {
            printf("  METEO   : %s\n", a.text);
            ++count_meteo;
        } else {
            printf("  ???     : %s  (mtype=%ld)\n", a.text, a.mtype);
        }
    }


    /* TODO 4: dopo il loop stampare riepilogo finale                     */
    puts("\n=== STATISTICHE FINALI ===");
    printf("Allarmi Polizia gestiti : %d\n", count_polizia);
    printf("Allarmi Meteo   gestiti : %d\n", count_meteo);

    return 0;
}