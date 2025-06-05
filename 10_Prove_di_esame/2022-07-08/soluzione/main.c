#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid;
    key_t msg_req_key = ftok(".", 'a'); //TODO: definire chiave
	key_t msg_res_key = ftok(".", 'b'); //TODO: definire chiave

    //TODO: INIZIALIZZAZIONE CODE
    int coda_req = msgget(msg_req_key, IPC_CREAT|0664);
    int coda_res = msgget(msg_res_key, IPC_CREAT|0664);
	
    pid = fork();
    if (pid==0) {
        execl("./server","./server",NULL);
        _exit(0);
    }

    pid = fork();
    if (pid==0) {
        execl("./reader","./reader",NULL);
        _exit(0);
    }

    wait(NULL);
    wait(NULL);

    // TODO: eliminazione code
    msgctl(coda_req, IPC_RMID, NULL);
    msgctl(coda_res, IPC_RMID, NULL);

    return 0;
}
