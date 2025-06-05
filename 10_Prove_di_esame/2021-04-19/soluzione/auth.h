#ifndef _AUTH_H_
#define _AUTH_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>

#define MESSAGGIO_CLIENT 1
#define MESSAGGIO_SERVER 2
#define ELABORAZIONE 1


typedef struct {

    long type;
    pid_t PIDclient;
    pid_t PIDserver;
    int token;

} RichiestaAuth;

typedef struct {

    long type;
    int token;
    int esito;

} RispostaAuth;

typedef struct {

    long type;
    pid_t PID;
    int valore;
    int token;

} RichiestaElab;

typedef struct {

    long type;
    int esito;

} RispostaElab;



#define TOKEN_AUTH_REQ_TYPE 1
#define CONFERMA_AUTH_REQ_TYPE 2
#define ELAB_REQ_TYPE 3



void Auth(int id_coda_auth_req, int id_coda_auth_resp);
void Server(int id_coda_elab_req, int id_coda_elab_resp, int id_coda_auth_req, int id_coda_auth_resp);
void ClientAuth(int id_coda_auth_req, int id_coda_auth_resp, int id_coda_elab_req, int id_coda_elab_resp);
void ClientNonAuth(int id_coda_elab_req, int id_coda_elab_resp);

static inline void die(const char * msg){
    perror(msg);
    exit(1);
}

#endif /* _AUTH_H_ */
