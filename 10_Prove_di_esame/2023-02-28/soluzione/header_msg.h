#ifndef _HEADER_
#define _HEADER_

typedef struct {

    /* TBD: Definire la struttura, per inviare
            un valore di tipo intero
     */
    long tipo;
    int valore;

} messaggio_sensore;

typedef struct {

    /* TBD: Definire la struttura, per inviare
            un valore di tipo intero
     */
    long tipo;
    int valore;

} messaggio_collettore;

#define NUM_MESSAGGI_PER_SENSORE 5
#define NUM_SENSORI_PER_COLLETTORE 3
#define NUM_COLLETTORI 2


void sensore(int id_sensore, int id_queue_collettore);
void collettore(int id_collettore, int id_queue_collettore, int id_queue_server);
void server(int id_queue_server);

#endif