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
		produci_tipo_1(m, valore);

		sleep(1);
	}

}


void produttore_2(MonitorPC * m)
{
    srand(getpid());

	for(int i=0; i<4; i++) {

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 2 */
		produci_tipo_2(m, valore);

		sleep(1);
	}

}


void consumatore_1(MonitorPC * m)
{

	for(int i=0; i<8; i++) {

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 1 */
		consuma_tipo_1(m, &valore);

		sleep(1);
	}

}


void consumatore_2(MonitorPC * m)
{
	for(int i=0; i<8; i++) {

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 2 */
		consuma_tipo_2(m, &valore);

		sleep(1);
	}
}

int main(int argc, char *argv[])
{

	/* TBD: creare e inizializzare l'oggetto monitor (metodo "inizializza") */
	int shmid = shmget(IPC_PRIVATE, sizeof(MonitorPC), IPC_CREAT | 0664);
	if (shmid<0) die("Errore shmget");

	MonitorPC *m = (MonitorPC *)shmat(shmid, NULL, 0);
	if (m == (void *)-1) die("Errore shmat");
	inizializza(m);

	int i;
	for(i=0; i<2; i++) {

		/* TBD: avviare 2 produttori di tipo 1 */
		pid_t pid = fork();
		if (pid < 0) die("Errore fork produttore tipo 1");
		else if (pid == 0) {
			produttore_1(m);
			exit(0);
		}
	}

	for(i=0; i<2; i++) {

		/* TBD: avviare 2 produttori di tipo 2 */
		pid_t pid = fork();
		if (pid < 0) die("Errore fork produttore tipo 2");
		else if (pid == 0) {
			produttore_2(m);
			exit(0);
		}
	}

	/* TBD: avviare consumatore di tipo 1 */
	pid_t pid_cons1 = fork();
	if (pid_cons1 < 0) die("Errore fork consumatore tipo 1");
	else if (pid_cons1 == 0) {
		consumatore_1(m);
		exit(0);
	}

	/* TBD: avviare consumatore di tipo 2 */
	pid_t pid_cons2 = fork();
	if (pid_cons2 < 0) die("Errore fork consumatore tipo 2");
	else if (pid_cons2 == 0) {
		consumatore_2(m);
		exit(0);
	}



	for(i=0; i<2; i++) {

		/* TBD: attendere terminazione produttori di tipo 1 */
		pid_t pid = wait(NULL);
		if (pid < 0) die("Errore wait produttore tipo 1");
		else printf("Produttore tipo 1 con PID %d terminato\n", pid);
	}


	for(i=0; i<2; i++) {

		/* TBD: attendere terminazione produttori di tipo 2 */
		pid_t pid = wait(NULL);
		if (pid < 0) die("Errore wait produttore tipo 2");
		else printf("Produttore tipo 2 con PID %d terminato\n", pid);
	}

	/* TBD: attendere terminazione consumatori di tipo 1 */
	pid_t pid = waitpid(pid_cons1, NULL, 0);
	if (pid < 0) die("Errore wait consumatore tipo 1");
	else printf("Consumatore tipo 1 con PID %d terminato\n", pid);

	/* TBD: attendere terminazione consumatori di tipo 2 */
	pid = waitpid(pid_cons2, NULL, 0);
	if (pid < 0) die("Errore wait consumatore tipo 2");
	else printf("Consumatore tipo 2 con PID %d terminato\n", pid);

	

	/* TBD: rimuovere l'oggetto monitor */
	rimuovi(m);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}

