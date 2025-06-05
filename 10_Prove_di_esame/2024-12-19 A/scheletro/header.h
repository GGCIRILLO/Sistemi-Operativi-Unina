#include "monitor_hoare.h"
#include "semafori.h"

#define DIM 6
#define TOT_GIOCATTOLI 20

/*
    TODO: definire quanto necessario per la gestione del MonitorProdCons con vettore di stato 
*/


/*
    TODO: definire quanto necessario per la gestione del buffer mediante utilizzo di semafori
*/


typedef struct {
    /*
        TODO: completare struttura
    */
} MonitorProdCons;

typedef struct {
    /*
        TODO: completare struttura
    */
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