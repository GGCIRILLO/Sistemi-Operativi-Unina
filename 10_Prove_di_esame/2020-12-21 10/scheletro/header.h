#ifndef HEADER_H
#define HEADER_H

#define MAX_PRODOTTI 3

typedef struct {
    long tipo_richiesta;
    long mittente;
    int id_prodotto;
    int value;
} Msg_Req;

typedef struct {
    long pid;
    int id_prodotto;
    int scorta;
} Msg_Resp;

#endif
