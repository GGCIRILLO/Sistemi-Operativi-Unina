#ifndef _HEADER_MSG_
#define _HEADER_MSG_

/* TBD: Definire le strutture dati per l'invio dei messaggi */
#define RTS 1
#define OTS 2
#define MESSAGGIO 3

typedef struct {
    long type;
    char desc [30];
} service_msg;

typedef struct {
    long type;
    int val;
    int buff_id;
} msg;

#define NUM_BUFFER 3
#define NUM_SERVER (NUM_BUFFER*2)
#define NUM_RICHIESTE 4

#endif