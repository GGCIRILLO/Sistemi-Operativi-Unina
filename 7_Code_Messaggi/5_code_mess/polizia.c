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

int main(int argc, char *argv[])
{
    /* TODO 1: controllare argc, ricavare qid dalla stringa argv[1]        */
    if (argc != 2) die("Errore argc");
    int qid = atoi(argv[1]);
    if (qid <= 0) die("qid Polizia");
    /* TODO 2: srand(time(NULL)+getpid()), preparare array con 4 stringhe  */
    srand(getpid()+time(NULL));
    char *arr[] = {"Furto", "Vandalismo", "Aggressione", "Incendio"};
    /* TODO 3: ciclo di 8 iterazioni:                                      */
    /*         - scegliere stringa random                                  */
    /*         - costruire Alert con mtype = MSG_POLIZIA                   */
    /*         - msgsnd                                                    */
    /*         - printf log opzionale                                      */
    /*         - usleep(200000)                                            */
    Alert a;
    a.mtype = MSG_POLIZIA;

    for (int i=0;i<8;i++){
        int n = rand()%4;
       
        strcpy(a.text, arr[n]);

        if (msgsnd(qid, &a, sizeof(Alert)-sizeof(long), 0)==-1){
            die("Errore msgsnd");
        }
        printf("[POLIZIA] inviato: %s\n", a.text);
        usleep(200000);
    }

    /* TODO 4: inviare messaggio finale "FINE" e terminare                 */
    strcpy(a.text, "FINE");
    if (msgsnd(qid, &a, sizeof(Alert)-sizeof(long), 0)==-1){
            die("Errore msgsnd FINE");
    }
    return 0;
}