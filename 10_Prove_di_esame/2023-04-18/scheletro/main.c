#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#include "prodcons.h"


void produttore_1(MonitorPC * m)
{
	srand(getpid());

	for(int i=0; i<4; i++) {

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 1 */

		sleep(1);
	}

}


void produttore_2(MonitorPC * m)
{
    srand(getpid());

	for(int i=0; i<4; i++) {

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 2 */

		sleep(1);
	}

}


void consumatore_1(MonitorPC * m)
{

	for(int i=0; i<8; i++) {

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 1 */

		sleep(1);
	}

}


void consumatore_2(MonitorPC * m)
{
	for(int i=0; i<8; i++) {

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 1 */

		sleep(1);
	}
}

int main(int argc, char *argv[])
{

	/* TBD: creare e inizializzare l'oggetto monitor (metodo "inizializza") */
    


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

}

