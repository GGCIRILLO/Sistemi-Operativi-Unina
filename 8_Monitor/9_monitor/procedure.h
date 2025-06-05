#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "monitor_hoare.h"

/* ---------- costanti ---------- */
#define N_SLOTS   3

#define LIBERO     0
#define PRENOTATO  1
#define OCCUPATO   2

/* TBD: definire le condition variables e il numero*/

/* condition variables */
#define CV_CLIENTI      0
#define CV_RIFORNITORI  1
#define NUM_COND        2

/* ---------- strutture ---------- */
typedef struct {
    int stato[N_SLOTS];      /* LIBERO / PRENOTATO / OCCUPATO         */

    /* TBD : completare la struttura con num ti liberi, occupati e monitor */

    int liberi;              /* # slot LIBERO                         */
    int occupati;            /* # slot OCCUPATO                       */
    Monitor m;               /* monitor Hoare                         */
} Warehouse;

/* ---------- prototipi ---------- */
void w_init     (Warehouse *w);              /* alloc & init monitor   */
void w_remove   (Warehouse *w);              /* remove monitor         */

/* CLIENTE */
int  w_prenota  (Warehouse *w);              /* ritorna indice slot    */
void w_conferma (Warehouse *w, int idx);

/* RIFORNITORE */
int  w_prenota_occupato(Warehouse *w);
void w_libera   (Warehouse *w, int idx);

#endif /* PROCEDURE_H */