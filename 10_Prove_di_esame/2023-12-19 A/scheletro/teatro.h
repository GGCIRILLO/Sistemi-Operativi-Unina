#include <pthread.h>

#ifndef HEADER_H
#define HEADER_H

/* TODO: Definire (se necessario) le macro di utilità */

typedef struct{
    
    int ID;
    int tipo;
    
} posto_teatro;

typedef struct {
    
    /* TODO: Aggiungere le variabili per la sincronizzazione */
    
    posto_teatro *p;
    
} LettScritt;

typedef struct {
    
    long tipo;
    int value;
    
} Msg_Posto;

void * clientT(void *);
void * viewerT(void *);

void scrivi_posto(LettScritt *ls, posto_teatro *);
void leggi_posto(LettScritt *ls, int);

void InizioLetturaPosto(LettScritt * ls);
void FineLetturaPosto(LettScritt * ls);
void FineScritturaPosto(LettScritt * ls);
void InizioScritturaPosto(LettScritt * ls);


#endif
