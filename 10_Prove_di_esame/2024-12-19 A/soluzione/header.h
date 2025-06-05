#include "monitor_hoare.h"
#include "semafori.h"
#include <stdlib.h>
#include <stdio.h>

#define DIM 6
#define TOT_GIOCATTOLI 20

/*
    TODO: definire quanto necessario per la gestione del MonitorProdCons con vettore di stato 
*/
#define LIBERO 0
#define IN_USO 1
#define OCC_GIOCO1 2
#define OCC_GIOCO2 3

#define CV_PROD 0
#define CV_CONS1 1
#define CV_CONS2 2

/*
    TODO: definire quanto necessario per la gestione del buffer mediante utilizzo di semafori
*/

#define MUTEX 0
#define BABBO 1
#define ELFI 2

typedef struct {
    /*
        TODO: completare struttura
    */
    int stato[DIM];
    int buffer[DIM];
    int num_liberi;
    int num_occupati;

    Monitor m;

} MonitorProdCons;

typedef struct {
    /*
        TODO: completare struttura
    */
    int buffer;
    int semid;
} BufferBabbo;

void inizializza_vettore(MonitorProdCons *pc);
void rimuovi_vettore(MonitorProdCons *pc);
void inizializza_buffer(BufferBabbo * bb);
void rimuovi_buffer(BufferBabbo * bb);

void Produttore(MonitorProdCons *pc);
void produci(MonitorProdCons *pc, int tipo);
void Consumatore1(MonitorProdCons *pc, BufferBabbo *bb);
void Consumatore2(MonitorProdCons *pc, BufferBabbo *bb);
void BabboNatale(BufferBabbo *bb);

static inline void die(const char*x){
    perror(x);
    exit(1);
} 