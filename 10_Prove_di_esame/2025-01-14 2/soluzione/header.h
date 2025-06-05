#ifndef _HEADER_H
#define _HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



typedef struct {

    /* TBD: Definire la struttura del messaggio di richiesta.
            La stessa struttura può essere usata sia per i messaggi dal client al server,
            sia per i messaggi dal server al database.
     */
    long tipo;
    int valore;
    int posizione;
    int pid_mittente;

} messaggio_richiesta;

typedef struct {

    /* TBD: Definire la struttura del messaggio di risposta.
            La stessa struttura può essere usata sia per i messaggi dal database al server,
            sia per i messaggi dal server al client.
     */
    long tipo;
    int valore;
    int posizione;
    int pid_mittente;

} messaggio_risposta;



#define NUMERO_RICHIESTE 3

#define PROCESSI_CLIENT 3

#define PROCESSI_SERVER 3

#define DIM_VETTORE 3

#define SCRITTURA 1
#define LETTURA 2

static inline void die(const char* msg){
    perror(msg);
    exit(1);
}


#endif