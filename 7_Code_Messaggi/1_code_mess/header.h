/*=================== HEADER FILE (header.h) ===================*/
#ifndef __HEADER
#define __HEADER

#define MESSAGGIO 1          /* COSTANTE: tipo usato in msq */

typedef char msg[40];        /* PAYLOAD MASSIMO DI UN MSG */

typedef struct {             /* ***STRUTTURA MESSAGGIO***   */
    long tipo;               /* OBBLIGATORIO, PRIMO CAMPO   */
    msg  mess;               /* TESTO                      */
} Messaggio;

/* PROTOTIPI DELLE TRE FUNZIONI PUBBLICHE */
void Produttore(int queue, char* m);
void Consumatore(int queue);
void printMsgInfo(int queue);
#endif
/*==============================================================*/