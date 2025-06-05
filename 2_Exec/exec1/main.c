#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, execl
#include <sys/wait.h>   // wait, WIFEXITED, WEXITSTATUS

int main() {
    int st; // Variabile per raccogliere lo stato di terminazione del figlio

    // Creazione del processo figlio
    pid_t pid = fork();

    if (pid < 0) {
        // Se fork fallisce, stampa errore e termina
        perror("fork fallita");
        exit(1);
    }

    if (pid == 0) {
        // === CODICE DEL FIGLIO ===

        // Stampa il PID del figlio
        printf("[Figlio] PID %d\n", getpid());

        // Il figlio rimpiazza se stesso eseguendo il comando `ls -l`
        execl("/bin/ls", "ls", "-l", NULL);

        // Se exec fallisce (ritorna), stampa errore e termina con codice 1
        perror("exec fallita");
        exit(1);
    } else {
        // === CODICE DEL PADRE ===

        // Stampa il PID del padre
        printf("[Padre] PID %d\n", getpid());

        // Il padre attende la terminazione di un figlio e ne salva il PID
        pid_t terminated_pid = wait(&st);

        // Controlla se il figlio è terminato normalmente (con exit)
        if (WIFEXITED(st)) {
            // Stampa il PID del figlio terminato e il suo codice di uscita
            printf("[Padre] Il figlio %d ha terminato con stato di uscita %d\n",
                   terminated_pid, WEXITSTATUS(st));
        } else {
            // Il figlio è terminato per un segnale o altro
            printf("[Padre] Il figlio %d NON è terminato normalmente\n", terminated_pid);
        }
    }

    return 0; // Fine del programma padre
}