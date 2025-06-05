#ifndef _HEADER_
#define _HEADER_

typedef struct {

    //TODO completare struttura messaggio

} messaggio_sensore;

typedef struct {

    l//TODO completare struttura messaggio

} messaggio_collettore;


#define NUM_MESSAGGI_PER_SENSORE 5
#define NUM_SENSORI 3

void sensore(int id_sensore, int id_queue_collettore);
void collettore(int id_queue_collettore, int id_queue_server);

#endif