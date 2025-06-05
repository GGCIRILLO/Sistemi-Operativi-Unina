#ifndef _HEADER_PRODCONS_H_
#define _HEADER_PRODCONS_H_

#include <sys/sem.h>

#define DIM_BUFF 2

typedef struct {

    int valore[DIM_BUFF];
    //TODO: aggiungere variabili per gestione circolare con semafori

} BufferProdCons;

#endif