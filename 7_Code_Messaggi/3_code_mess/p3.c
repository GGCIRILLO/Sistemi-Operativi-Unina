#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

#define N_P1 11
#define N_P2 11

static void die(const char* msg){
    perror(msg);
    exit(1);
}


int main() {

	printf("[P3] Avvio\n");
    key_t k = ftok(FTOK_PATH_Q, FTOK_CHAR_Q);
    if (k == -1) die("ftok");
    
	int qid = msgget(k, 0);
    if (qid == -1) die("msgget attach");

    /* 3. Variabili per il calcolo delle medie */
    int   cnt_p1 = 0,   cnt_p2 = 0;
    float sum_p1 = 0.0f, sum_p2 = 0.0f;

    struct msg_calc msg;


    /* 4. Ricevi finché non hai 11 valori da P1 e 11 da P2 */
    while (cnt_p1 < N_P1 || cnt_p2 < N_P2) {

        /* msgtyp = 0 → preleva il primo messaggio disponibile */
        if (msgrcv(qid,&msg, sizeof(struct msg_calc) - sizeof(long),
                   0,            /* nessun filtro sul tipo          */
                   0) == -1)     /* operazione bloccante            */
        {
            die("msgrcv");
        }

        /* Smista in base al campo “processo” */
        if (msg.processo == P1 && cnt_p1 < N_P1) {
            ++cnt_p1;
            sum_p1 += msg.numero;
            printf("[P3] ricevuto %2d/%d da P1: %.4f\n",
                   cnt_p1, N_P1, msg.numero);
        }
        else if (msg.processo == P2 && cnt_p2 < N_P2) {
            ++cnt_p2;
            sum_p2 += msg.numero;
            printf("[P3] ricevuto %2d/%d da P2: %.4f\n",
                   cnt_p2, N_P2, msg.numero);
        }
    }

    /* 5. Risultato finale */
    printf("\n=== RISULTATO FINALE ===\n");
    printf("Media P1 (%d valori) = %.4f\n", N_P1, sum_p1 / N_P1);
    printf("Media P2 (%d valori) = %.4f\n", N_P2, sum_p2 / N_P2);

	return 0;
}