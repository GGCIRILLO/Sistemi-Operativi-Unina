#ifndef CHAT_HEADER_H
#define CHAT_HEADER_H

#define MAX_TEXT 256          /* lunghezza massima del messaggio            */
#define FTOK_PATH "."         /* path da dare a ftok() (file esistente)     */

/* valori da mettere nel campo mtype della struttura msg */
#define MSG_DATA 1            /* messaggio “normale”                        */
#define MSG_EXIT 2            /* token di terminazione ("exit")             */


typedef struct {
    long mtype;               /* MSG_DATA oppure MSG_EXIT                   */
    char text[MAX_TEXT];      
} Chat_msg;


#endif /* CHAT_HEADER_H */