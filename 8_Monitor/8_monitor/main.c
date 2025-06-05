/* MAIN – spool di stampa con aging */

#include "procedure.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/* costanti di test */
#define NUM_URGENTI   1
#define NUM_NORMALI   2
#define NUM_BASSE     2
#define JOB_PER_PROD  5

static void producer_loop(Spooler *s, int prio, int pause_sec)
{
	srand(time(NULL)^getpid());
    /* TBD: ciclo che invoca submit_job() JOB_PER_PROD volte           */
	for(int i=0;i<JOB_PER_PROD;i++){
		submit_job(s, prio);
		sleep(pause_sec);
	}
}

static void printer_loop(Spooler *s)
{
    /* TBD: ciclo che invoca get_next_job() finché non consuma
             NUM_TOTALI = JOB_PER_PROD*(# tot produttori)               */

	int tot_job = JOB_PER_PROD * (NUM_URGENTI + NUM_NORMALI + NUM_BASSE);
	const char *tag[] = { "URG", "NORM", "LOW" };

    for (int i = 0; i < tot_job; ++i) {
        print_job pj = get_next_job(s);
    
        sleep(1);   /* simulazione stampa */
    }
}
static void die(const char* msg){
	perror(msg);
	exit(1);
}

int main(void)
{
    int shm_id;
    Spooler *s = NULL;

    /* TBD: allocare shared memory per Spooler, attach, spooler_init   */
	shm_id = shmget(IPC_PRIVATE, sizeof(Spooler), IPC_CREAT|0664);
	if (shm_id<0) die("shmget");
	
	s = (Spooler*) shmat(shm_id, NULL, 0);
	if(s==(void*)-1) die("shmat");

	spooler_init(s);

    /* fork printer */
    /* TBD: fork, nel figlio chiamare printer_loop                     */
	pid_t pid = fork();
	if (pid<0) die("fork");
	else if (pid ==0){
		printf("[%d] Figlio Consumatore\n", getpid());
		printer_loop(s);
		exit(0);
	}

    /* fork produttori URG/NORM/LOW */
    /* TBD: generare processi e chiamare producer_loop con
             priorità 0,1,2 e pause 2s o 1s a seconda della classe     */
	for(int i=0;i<NUM_URGENTI;i++){
		pid = fork();
		if (pid==0){
			producer_loop(s, PRIO_URG, 2);
			_exit(0);
		}
	}

	for (int i=0;i<NUM_NORMALI;i++){
		pid = fork();
		if(pid==0){
			producer_loop(s, PRIO_NORM, 1);
			_exit(0);
		}
	}

	for (int i=0;i<NUM_BASSE;i++){
		pid = fork();
		if(pid==0){
			producer_loop(s, PRIO_LOW, 1);
			_exit(0);
		}
	}
	

    /* attesa figli */
    /* TBD: wait su tutti i figli                                      */
	int num_figli = 1 + NUM_URGENTI + NUM_NORMALI + NUM_BASSE; /* printer + producers */
	for (int i=0;i<num_figli;i++) wait(NULL);

    /* cleanup */
    /* TBD: spooler_remove e shmctl IPC_RMID                           */
	spooler_remove(s);
	shmctl(shm_id, IPC_RMID, 0);

    return 0;
}