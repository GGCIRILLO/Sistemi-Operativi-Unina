#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include "header.h"

static void die(const char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    /* TODO 1: validare argc, estrarre qid                                */
    if (argc != 2) die("Errore argc");
    int qid = atoi(argv[1]);
    if (qid<=0) die("qid Meteo");
    /* TODO 2: srand + array stringhe ("Temporale", "Neve", ...)          */
    srand(getpid()+time(NULL));
    char *arr[] = {"Temporale", "Vento", "Neve", "Grandine"};
    /* TODO 3: 8 iterazioni:                                              */
    /*         - scegliere stringa random                                 */
    /*         - inviare Alert con mtype = MSG_METEO                      */
    /*         - usleep(500000)                                           */
    Alert a;
    a.mtype = MSG_METEO;
    for (int i=0;i<8;i++){
        int n = rand()%4;
        strcpy(a.text, arr[n]);

        if (msgsnd(qid, &a, sizeof(Alert)-sizeof(long), 0)==-1){
            die("Errore msgsnd");
        }
        printf("[METEO] inviato: %s\n", a.text);
        usleep(500000);
    }
    /* TODO 4: messaggio "FINE" con mtype = MSG_METEO                     */
    strcpy(a.text, "FINE");
    if (msgsnd(qid, &a, sizeof(Alert)-sizeof(long), 0)==-1){
            die("Errore msgsnd FINE");
    }
    return 0;
}