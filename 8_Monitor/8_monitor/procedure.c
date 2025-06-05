/* IMPLEMENTAZIONE DELLE PROCEDURE */

#include "procedure.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static const char *PRIO_STR[] = { "URG", "NORM", "LOW" };

/* ---------- Macro per le condition ---------- */
#define NOT_FULL  0
#define NOT_EMPTY 1

/* ---------- Funzioni ausiliarie sullo heap ---------- */
/* ---------- helper macro sul heap ---------- */
#define PARENT(i)   (((i) - 1) / 2)
#define LEFT(i)     ((2 * (i)) + 1)
#define RIGHT(i)    ((2 * (i)) + 2)

/* ritorna 1 se a ha priorità più alta di b (ricorda: 0 < 1 < 2) */
static int prio_better(const print_job *a, const print_job *b)
{
    if (a->prio != b->prio)        /* più bassa la cifra, più alta la prio */
        return a->prio < b->prio;
    /* stessa prio → più vecchio = migliore */
    return a->enqueue_ts < b->enqueue_ts;
}

/* ---------- heap_push -------------------------------------------------- */
static void heap_push(Spooler *s, print_job job)
{
    int i = s->count++;
    s->heap[i] = job;

    /* sift-up */
    while (i > 0 && prio_better(&s->heap[i], &s->heap[PARENT(i)])) {
        print_job tmp = s->heap[i];
        s->heap[i] = s->heap[PARENT(i)];
        s->heap[PARENT(i)] = tmp;
        i = PARENT(i);
    }
}

/* ---------- heap_pop  (estrae il job “migliore”) ----------------------- */
static print_job heap_pop(Spooler *s)
{
    print_job top = s->heap[0];
    s->heap[0] = s->heap[--(s->count)];   /* sposta l’ultimo in radice */

    /* sift-down */
    int i = 0;
    while (1) {
        int l = LEFT(i), r = RIGHT(i), best = i;

        if (l < s->count && prio_better(&s->heap[l], &s->heap[best]))
            best = l;
        if (r < s->count && prio_better(&s->heap[r], &s->heap[best]))
            best = r;

        if (best == i) break;             /* heap property ok */
        print_job tmp = s->heap[i];
        s->heap[i] = s->heap[best];
        s->heap[best] = tmp;
        i = best;
    }
    return top;
}

/* ---------- aging: promuove LOW → NORM dopo 5 s ------------------------ */
static void heap_promote_aging(Spooler *s)
{
    time_t now = time(NULL);
    int changed = 0;

    for (int i = 0; i < s->count; ++i) {
        if (s->heap[i].prio == PRIO_LOW &&
            now - s->heap[i].enqueue_ts >= 5)
        {
            printf("[AGING] promote pid=%d  LOW→NORM\n", s->heap[i].pid);
            s->heap[i].prio = PRIO_NORM;
            changed = 1;
        }
    }

    /* se abbiamo cambiato priorità a qualcuno, ricostruisci il heap    */
    if (changed) {
        /* heapify bottom-up */
        for (int i = (s->count / 2) - 1; i >= 0; --i) {
            int parent = i;
            while (1) {
                int l = LEFT(parent), r = RIGHT(parent), best = parent;

                if (l < s->count && prio_better(&s->heap[l], &s->heap[best]))
                    best = l;
                if (r < s->count && prio_better(&s->heap[r], &s->heap[best]))
                    best = r;

                if (best == parent) break;
                print_job tmp = s->heap[parent];
                s->heap[parent] = s->heap[best];
                s->heap[best] = tmp;
                parent = best;
            }
        }
    }
}

/* ---------- API ---------- */

void spooler_init(Spooler *s)
{
    /* TBD: inizializzare count, init_monitor(...)               */
    s->count=0;
    init_monitor(&(s->m), 2);
}

void spooler_remove(Spooler *s)
{
    /* TBD: remove_monitor(...);                                    */
    remove_monitor(&(s->m));
}

/* ---------- Produttore ---------- */
void submit_job(Spooler *s, int prio)
{
    /* TBD: enter_monitor                                             */
    /*      while (coda piena) wait_condition(NOT_FULL)               */
    /*      genera job, heap_push                                     */
    /*      signal_condition(NOT_EMPTY)                               */
    /*      leave_monitor                                             */
    enter_monitor(&(s->m));
    while(s->count==HEAP_DIM){
        printf("[P %d] coda piena → wait\n", getpid());
        wait_condition(&(s->m), NOT_FULL);
        printf("[P %d] ripreso\n", getpid());
    }

    print_job j = {
        .pid         = getpid(),
        .prio        = prio,
        .enqueue_ts  = time(NULL),
        .pages       = (rand() % 10) + 1
    };

    heap_push(s, j);

    

    printf("[P %d] submit  %s  pages=%d  (count=%d)\n",
           j.pid, PRIO_STR[j.prio], j.pages, s->count);


    signal_condition(&(s->m), NOT_EMPTY);

    leave_monitor(&(s->m));
}

/* ---------- Consumer (printer) ---------- */
print_job get_next_job(Spooler *s)
{
    /* TBD: enter_monitor                                             */
    /*      while (coda vuota) wait_condition(NOT_EMPTY)              */
    /*      heap_promote_aging(); job = heap_pop();                   */
    /*      signal_condition(NOT_FULL)                                */
    /*      leave_monitor; return job;                               */
    enter_monitor(&(s->m));

    while(s->count==0){
        printf("[C] coda vuota → wait\n");
        wait_condition(&(s->m), NOT_EMPTY);
        printf("[C] ripreso\n");
    }

    heap_promote_aging(s);
    print_job j = heap_pop(s);

    printf("[C] dequeue %s  pid=%d  pages=%d  (count=%d)\n",
           PRIO_STR[j.prio], j.pid, j.pages, s->count);

    signal_condition(&(s->m), NOT_FULL);
    leave_monitor(&(s->m));

    return j;
}