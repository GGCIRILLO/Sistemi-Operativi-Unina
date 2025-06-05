			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#include "semafori.h"

#define DIM 4

// TODO: definire semafori

#define NPROD 4
#define NCONS 2

#define PRODS 4
#define CONS 8

typedef struct {
	
	// TODO: completare campi struct

} BufferMutuaEx;

void produci_tipo_1(BufferMutuaEx * buf, int semid, int val);
void produci_tipo_2(BufferMutuaEx * buf, int semid, int val);
void consuma_tipo_1(BufferMutuaEx * buf, int semid);
void consuma_tipo_2(BufferMutuaEx * buf, int semid);



#endif
