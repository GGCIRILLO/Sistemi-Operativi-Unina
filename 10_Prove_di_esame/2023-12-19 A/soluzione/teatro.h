#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef HEADER_H
#define HEADER_H

/* TODO: Definire (se necessario) le macro di utilità */
#define PLATEA 0
#define BALCONATA 1

typedef struct{

    int ID;
    int tipo;

} posto_teatro;

typedef struct {

    /* TODO: Aggiungere le variabili per la sincronizzazione */

    posto_teatro *p;

    int lettori;
    int scrittori;
    int lettori_in_attesa;
    int scrittori_in_attesa;
    pthread_mutex_t mutex;
    pthread_cond_t cv_lettura;
    pthread_cond_t cv_scrittura;

} LettScritt;

typedef struct{

    long tipo;
    int value;

} Msg_Posto;

void *clientT(void *);
void *viewerT(void *);

void scrivi_posto(LettScritt *ls, posto_teatro *);
void leggi_posto(LettScritt *ls, int);

void InizioLetturaPosto(LettScritt *ls);
void FineLetturaPosto(LettScritt *ls);
void FineScritturaPosto(LettScritt *ls);
void InizioScritturaPosto(LettScritt *ls);

static inline void die(const char *s){
    perror(s);
    exit(1);
}

#endif
