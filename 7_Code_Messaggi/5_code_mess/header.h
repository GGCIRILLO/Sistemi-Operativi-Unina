#ifndef HEADER_H
#define HEADER_H

#define FTOK_PATH "."           
#define MAX_TXT   64

#define MSG_POLIZIA  1          /* mtype per allarme di Polizia (prio alto) */
#define MSG_METEO    2          /* mtype per allarme Meteo   (prio basso)  */

typedef struct {
    long  mtype;                /* deve essere long e primo campo         */
    char  text[MAX_TXT];        /* descrizione evento                     */
} Alert;

#endif /* HEADER_H */