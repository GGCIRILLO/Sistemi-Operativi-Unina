#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "header.h"

#define N_MSG 11
#define MIN_VAL  10    
#define MAX_VAL 100    

static void send_value(int qid, long tipo){
    struct msg_calc m;
    m.processo = tipo;
    m.numero   = generaFloat(MIN_VAL, MAX_VAL);

    if (msgsnd(qid, &m, sizeof(struct msg_calc) - sizeof(long), 0) == -1)
        perror("msgsnd");

    printf("[P%ld] inviato: %.4f\n", m.processo, m.numero);

}

static void die(const char* msg){
    perror(msg);
    exit(1);
}

int main() {

    printf("[P1] Avvio\n");

    key_t k = ftok(FTOK_PATH_Q, FTOK_CHAR_Q);
    if (k == -1) die("Errore ftok");

    int qid = msgget(k, 0);
    if (qid == -1) die("Errore msgget");

    srand(time(NULL) ^ getpid());

    for (int i = 0; i < N_MSG; i++) {
        send_value(qid, P1);          
        usleep(100000);
    }

    printf("[P1] terminato\n");

	return 0;
}