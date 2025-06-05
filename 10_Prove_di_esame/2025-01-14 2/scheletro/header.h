#ifndef _HEADER_H
#define _HEADER_H


typedef struct {

    /* TBD: Definire la struttura del messaggio di richiesta.
            La stessa struttura può essere usata sia per i messaggi dal client al server,
            sia per i messaggi dal server al database.
     */

} messaggio_richiesta;

typedef struct {

    /* TBD: Definire la struttura del messaggio di risposta.
            La stessa struttura può essere usata sia per i messaggi dal database al server,
            sia per i messaggi dal server al client.
     */

} messaggio_risposta;



#define NUMERO_RICHIESTE 3

#define PROCESSI_CLIENT 3

#define PROCESSI_SERVER 3

#define DIM_VETTORE 3


#endif