#define MSG_TYPE_CONTROL_PROXY 1
#define MSG_TYPE_ARRIVI 2
#define MSG_TYPE_PARTENZE 3

#define REQUEST_TO_SEND 4
#define OK_TO_SEND 5

extern int coda_RTS;
extern int coda_OTS;

// Struttura che definisce un Volo
typedef struct {
    
    /* To be completed */
    long tipo; 
    
    int ID;
    char direzione [10];
    char citta_partenza [20];
    char citta_arrivo [20];

}Volo;

/* Struttura che definisce un messaggio di controllo per implementare
 * la send sincrona
 */
typedef struct {
    
    /* To be completed */
    long tipo;
        
}Control;

void controllore(int ds_queue_control_proxy);
void proxy(int ds_queue_control_proxy, int ds_queue_proxy_gestori);
void gestore_arrivi(int ds_queue_proxy_gestori);
void gestore_partenze(int ds_queue_proxy_gestori);

void initServiceQueues();
void removeServiceQueues();
