#include "header.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>


int main() {
	// TODO: creazione coda di messaggi
	key_t k_q = ftok(".", 'q');
	int id_coda = msgget(k_q, 0664); // permessi per solo ricezione
	if (id_coda<0) die("msgget");

	struct coordinates c;
	struct message mess;
	int ret;
	sleep(1);
	for(int i=0; i<N_COMPUTE_PER_THREAD*NTHREADS_PROD; i++){
		// TODO: ricezione messaggio dalla coda
		ret = msgrcv(id_coda, (void*)&mess, sizeof(mess)-sizeof(long), 0, 0);
		if (ret<0) die("msgrcv");
		c=mess.coords;

		printf("[Plotter: %d, %d]\n",c.x, c.y);
	}

	// TODO: rimozione coda
	msgctl(id_coda, IPC_RMID, NULL);

	return 0;
}	
