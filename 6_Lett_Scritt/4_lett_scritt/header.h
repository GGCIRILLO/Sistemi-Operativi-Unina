#ifndef HEADER_H
#define HEADER_H

#define SYNCH 0
#define MUTEXL 1
#define MUTEXS 2
#define MUTEX 3

#define NUM_S 2
#define NUM_L 2

typedef struct {
    int status_code;
    char diagnostic_message[32];
    int numlettori;
    int numscrittori;
} Monitor; 

void Lettore(int, Monitor*, int);
void Scrittore(int, Monitor*, int);

#endif