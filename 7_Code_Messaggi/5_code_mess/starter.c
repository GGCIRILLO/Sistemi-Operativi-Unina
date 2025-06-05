#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include "header.h"

static void die(const char* msg){
    perror(msg);
    exit(1);
}

int main(void)
{
    /* TODO 1: creare coda */
    key_t k = IPC_PRIVATE;
    int qid = msgget(k, IPC_CREAT|0664);
    if(qid<0) die("Errore msgget");

    /* TODO 2: fork & exec dei tre ruoli (polizia, meteo, centro)          */
    /*         passare l'id di coda come argv[1]                           */
    const char *exe[] = {"./polizia", "./meteo", "./centro"};
    for (int i=0;i<3;i++){
        pid_t pid = fork();
        if (pid<0) die("Errore fork");
        if(pid==0){
            char str[12];
            sprintf(str, "%d", qid);
            execl(exe[i], exe[i], str, (char*)NULL);
            die("Errore exec");
        }
    }
    /* TODO 3: attendere con wait() i tre figli                            */
    for (int i=0;i<3;i++) wait(NULL);

    /* TODO 4: eliminare la coda con msgctl IPC_RMID                       */
    msgctl(qid, IPC_RMID, 0);

    return 0;
}