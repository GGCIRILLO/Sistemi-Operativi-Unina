#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"

int coda_RTS;
int coda_OTS;

int main(){

        pid_t pid;
        int ds_queue_control_proxy, ds_queue_proxy_gestori;
    
        //create queues
        int key_queue_control_proxy = /* TBD: definire la chiave */
        int key_queue_proxy_gestori = /* TBD: definire la chiave */
    
        ds_queue_control_proxy = /* TBD: Creare la coda tra Controllore e Proxy */
        ds_queue_proxy_gestori = /* TBD: Creare la coda tra Proxy e gestor */
    
        /* Creare le code di servizio per implementare la send sincrona */
        
        printf("[master] Code create...\n");
        printf("[master] ...........ds_queue_control_proxy: %d\n", ds_queue_control_proxy);
        printf("[master] ...........ds_queue_proxy_gestori: %d\n", ds_queue_proxy_gestori);
    

        int i;
        for (i=0; i<4; i++){
            /* TBD: Creare i 4 processi:
             * - Processo Controllore;
             * - Processo Proxy;
             * - Processo Gestore Arrivi
             * - Processo Gestore Partenze
             */
        }
    
        for (i=0; i<4; i++){
            /*TBD: Attendere la terminazione dei processi creati in precedenza */
        }

        /* TBD: Deallocare le code create */
         
        printf("[master] Rimozione code OK!\n");
    
        return 0;
}
