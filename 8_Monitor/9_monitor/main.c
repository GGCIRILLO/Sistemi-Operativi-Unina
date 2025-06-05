/* MAIN – test magazzino con prenotazione */

#include "procedure.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define NUM_CLIENTI      5
#define NUM_RIFORNITORI  2
#define CICLI_CLIENTE    6
#define CICLI_RIF        6

static void die(const char *msg) { perror(msg); exit(EXIT_FAILURE); }

/* ---------------- worker client ---------------- */
static void client_loop(Warehouse *w)
{
    /* TBD: per CICLI_CLIENTE volte
             int idx = w_prenota(...)
             ... lavoro lento già in w_prenota ...
             w_conferma(...);                                      */

    srand(time(NULL)^getpid());

    for (int i=0;i<CICLI_CLIENTE;i++){
        int idx = w_prenota(w);
        
        sleep(2);

        w_conferma(w, idx);
    }
}

/* ---------------- worker rifornitore ------------ */
static void rif_loop(Warehouse *w)
{
    /* TBD: per CICLI_RIF volte
             int idx = w_prenota_occupato(...)
             ... lavoro lento già in w_prenota_occupato ...
             w_libera(...);                                        */
    for (int i=0;i<CICLI_RIF;i++){
        int idx = w_prenota_occupato(w);

        sleep(1);                        

        w_libera(w, idx);
    }
}

int main(void)
{
    /* ---------- shared memory ---------- */
    int id = shmget(IPC_PRIVATE, sizeof(Warehouse), IPC_CREAT | 0666);
    if (id < 0) die("shmget");

    Warehouse *w = shmat(id, NULL, 0);
    if (w == (void *)-1) die("shmat");

    w_init(w);

    /* ---------- fork clienti ---------- */
    for (int i = 0; i < NUM_CLIENTI; ++i) {
        pid_t pid = fork();
        if (pid < 0) die("fork");
        if (pid == 0) { client_loop(w); _exit(0); }
    }

    /* ---------- fork rifornitori ---------- */
    for (int i = 0; i < NUM_RIFORNITORI; ++i) {
        pid_t pid = fork();
        if (pid < 0) die("fork");
        if (pid == 0) { rif_loop(w); _exit(0); }
    }

    /* ---------- attesa figli ---------- */
    int tot = NUM_CLIENTI + NUM_RIFORNITORI;
    while (tot--) wait(NULL);

    /* ---------- cleanup ---------- */
    w_remove(w);
    shmctl(id, IPC_RMID, 0);

    puts("Padre terminato.");
    return 0;
}