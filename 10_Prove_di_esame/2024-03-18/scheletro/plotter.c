#include "header.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>


int main() {
	// TODO: creazione coda di messaggi
	struct coordinates c;
	struct message mess;
	int ret;
	sleep(1);
	for(int i=0; i<N_COMPUTE_PER_THREAD*NTHREADS_PROD; i++){
		// TODO: ricezione messaggio dalla coda
		printf("[Plotter: %d, %d]\n",c.x, c.y);
	}

	// TODO: rimozione coda
	return 0;
}	
