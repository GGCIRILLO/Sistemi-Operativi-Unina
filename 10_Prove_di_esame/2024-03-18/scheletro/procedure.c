#include "header.h"

void inizializza(struct monitor* m){

    // TODO: inizializza variabile di supporto per rate limiting e buffer circolare

    // TODO: inizializza mutex e cv necessarie
}

void rimuovi (struct monitor* m){
    // TODO: rimuovi strutture inizializzate
}

void send_coordinates(struct monitor* m, struct coordinates* c){
    //TODO: entra nel monitor e deposita le coordinate se si è sotto al limite di messaggi al secondo
}

void receive_coordinates(struct monitor* m, struct coordinates* c){
    //TODO: entra nel monitor e consuma
}

void reset_rate(struct monitor* m){
    //TODO: reset rate
}





