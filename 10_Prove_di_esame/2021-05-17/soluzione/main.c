#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "prodcons.h"

void *produttore_1(void *p)
{
	MonitorPC *pc = (MonitorPC *)p;
	for (int i = 0; i < 4; i++)
	{

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 1 */
		produci_tipo_1(pc, valore);

		sleep(1);
	}

	pthread_exit(NULL);
}

void *produttore_2(void *p)
{
	MonitorPC *pc = (MonitorPC *)p;
	for (int i = 0; i < 4; i++)
	{

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 2 */
		produci_tipo_2(pc, valore);

		sleep(1);
	}

	pthread_exit(NULL);
}

void *consumatore_1(void *p)
{
	MonitorPC *pc = (MonitorPC *)p;
	for (int i = 0; i < 8; i++)
	{

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 1 */
		consuma_tipo_1(pc, &valore);

		sleep(1);
	}

	pthread_exit(NULL);
}

void *consumatore_2(void *p)
{
	MonitorPC *pc = (MonitorPC *)p;
	for (int i = 0; i < 8; i++)
	{

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 1 */
		consuma_tipo_2(pc, &valore);

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
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	int rc;
	int i;

	srand(time(NULL));

	/* TBD: creare e inizializzare l'oggetto monitor */
	MonitorPC *pc = malloc(sizeof(MonitorPC));
	inizializza(pc);

	for (i = 0; i < 2; i++)
	{

		/* TBD: avviare 2 produttori di tipo 1 */
		pthread_create(&thread_produttori_1[i], &attr, produttore_1, (void *)pc);
	}

	for (i = 0; i < 2; i++)
	{

		/* TBD: avviare 2 produttori di tipo 2 */
		pthread_create(&thread_produttori_2[i], &attr, produttore_2, (void *)pc);
	}

	/* TBD: avviare consumatore di tipo 1 */
	pthread_create(&thread_consumatore_1, &attr, consumatore_1, (void *)pc);

	/* TBD: avviare consumatore di tipo 2 */
	pthread_create(&thread_consumatore_2, &attr, consumatore_2, (void *)pc);

	for (i = 0; i < 2; i++)
	{

		/* TBD: attendere terminazione produttori di tipo 1 */
		pthread_join(thread_produttori_1[i], NULL);
	}

	for (i = 0; i < 2; i++)
	{

		/* TBD: attendere terminazione produttori di tipo 2 */
		pthread_join(thread_produttori_2[i], NULL);
	}

	/* TBD: attendere terminazione consumatori di tipo 1 */
	pthread_join(thread_consumatore_1, NULL);

	/* TBD: attendere terminazione consumatori di tipo 2 */
	pthread_join(thread_consumatore_2, NULL);

	/* TBD: rimuovere l'oggetto monitor */
	rimuovi(pc);
	free(pc);
	pthread_attr_destroy(&attr);

	return 0;
}
