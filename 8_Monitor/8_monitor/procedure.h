#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "monitor_signal_continue.h"
#include <time.h>

/* ---------- Costanti ---------- */
#define HEAP_DIM       6      /* dimensione massima della coda        */

#define PRIO_URG   0          /* urgente  */
#define PRIO_NORM  1          /* normale  */
#define PRIO_LOW   2          /* bassa    */

/* ---------- Strutture dati ---------- */
typedef struct {
    int    pid;              /* PID del processo che ha inviato il job   */
    int    prio;             /* priorità corrente (0–2)                  */
    time_t enqueue_ts;       /* timestamp di inserimento                 */
    int    pages;            /* numero di pagine da stampare             */
} print_job;

typedef struct {
    print_job heap[HEAP_DIM];
    int       count;         /* elementi presenti nello heap             */
    Monitor   m;             /* monitor Mesa (signal-and-continue)       */
} Spooler;

/* ---------- Prototipi ---------- */
void spooler_init   (Spooler *s);
void spooler_remove (Spooler *s);

void submit_job     (Spooler *s, int prio);        /* produttori  */
print_job get_next_job(Spooler *s);                /* consumer    */

#endif /* PROCEDURE_H */