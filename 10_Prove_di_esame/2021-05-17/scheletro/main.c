#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "prodcons.h"


void * produttore_1(void * p)
{
	MonitorPC * pc = (MonitorPC*)p;
	for(int i=0; i<4; i++) {

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 1 */

		sleep(1);
	}

	pthread_exit(NULL);
}


void * produttore_2(void * p)
{
    MonitorPC * pc = (MonitorPC*)p;
	for(int i=0; i<4; i++) {

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 2 */

		sleep(1);
	}

	pthread_exit(NULL);
}


void * consumatore_1(void * p)
{
	MonitorPC * pc = (MonitorPC*)p;
	for(int i=0; i<8; i++) {

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 1 */

		sleep(1);
	}

	pthread_exit(NULL);
}


void * consumatore_2(void * p)
{
	MonitorPC * pc = (MonitorPC*)p;
	for(int i=0; i<8; i++) {

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 1 */

		sleep(1);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

	pthread_t thread_produttori_1[2];
	pthread_t thread_produttori_2[2];
	pthread_t thread_consumatore_1;
	pthread_t thread_consumatore_2;

	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    
	int rc;
	int i;

	srand(time(NULL));

    
	/* TBD: creare e inizializzare l'oggetto monitor */

	for(i=0; i<2; i++) {

		/* TBD: avviare 2 produttori di tipo 1 */
	}

	for(i=0; i<2; i++) {

		/* TBD: avviare 2 produttori di tipo 2 */
	}

	/* TBD: avviare consumatore di tipo 1 */

	/* TBD: avviare consumatore di tipo 2 */


	
	
	for(i=0; i<2; i++) {

		/* TBD: attendere terminazione produttori di tipo 1 */
	}


	for(i=0; i<2; i++) {

		/* TBD: attendere terminazione produttori di tipo 2 */
	}

	/* TBD: attendere terminazione consumatori di tipo 1 */

	/* TBD: attendere terminazione consumatori di tipo 2 */

	

	/* TBD: rimuovere l'oggetto monitor */

	
	return 0;

}
