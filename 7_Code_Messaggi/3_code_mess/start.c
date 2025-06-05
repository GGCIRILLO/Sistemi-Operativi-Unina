#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

static void die(const char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char** argv) {

	key_t k = ftok(FTOK_PATH_Q, FTOK_CHAR_Q);
    if (k<0) die("Errore ftok");

    int qid = msgget(k, IPC_CREAT|0664);
    if(qid<0) die("Errore msgget");

    printf("[START] Coda creata id=%d\n", qid);

    const char *progs[] = {"./p1", "./p2", "./p3"};
    for (int i=0;i<3;i++){
        pid_t pid = fork();
        if (pid<0) die("Errore fork");
        if (pid==0){
            execl(progs[i], progs[i], (char*)NULL);
            die("Error exec");
        }
    }
    for (int i = 0; i < 3; ++i) wait(NULL); 

    msgctl(qid, IPC_RMID, 0);
	return 0;
}
