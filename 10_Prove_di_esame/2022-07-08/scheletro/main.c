#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid;
    key_t msg_req_key = //TODO: definire chiave
	key_t msg_res_key = //TODO: definire chiave

    //TODO: INIZIALIZZAZIONE CODE
	
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

    return 0;
}
