#ifndef _HEADER_H_
#define _HEADER_H_

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define TIPO 1
#define LETTORI 3

#define FTOK_PATH "."
#define FTOK_CHAR 'a'

typedef struct {

    // TODO: completare campi messaggio
    long tipo;
    int valore;

} Messaggio;

typedef struct {

    // TODO: completare inserendo i campi necessari a gestire il problema dei lettori-scrittori (unico scrittore)
    pthread_mutex_t mutex;

    pthread_cond_t cv_synch;

    int num_lettori;
    int scrittura; // 1 si, 0 no
    int valore;

} MonitorLS;

static inline void die (const char * msg){
    perror(msg);
    exit(1);
}

#endif
