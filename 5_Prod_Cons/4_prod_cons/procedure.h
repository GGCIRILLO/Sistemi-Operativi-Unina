#ifndef PROCEDURE_H
#define PROCEDURE_H

#define DIM_POSTI 80

#define NUM_FIGLI 50

typedef struct {
    unsigned int id_cliente;
    unsigned int stato;  // 0 = libero, 1 = occupato, 2 = in aggiornamento
} posto;

struct shm_data {
    posto teatro[DIM_POSTI];
    int disponibilita;
};

// Funzione cliente
void cliente(posto * teatro, int * disponibilita, int semid);

// Definizione indici semaforo
#define MUTEX 0

// Definizioni stato posti
#define LIBERO 0
#define OCCUPATO 1
#define IN_AGGIORNAMENTO 2

#endif