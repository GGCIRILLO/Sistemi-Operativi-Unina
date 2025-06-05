#include <stdio.h>      // printf()
#include <stdlib.h>     // exit(), rand(), srand()
#include <unistd.h>     // fork(), getpid()
#include <sys/wait.h>   // wait(), WIFEXITED(), WEXITSTATUS()
#include <time.h>       // time()

int main() {
    int wstatus;        // Variabile dove il padre riceve lo stato del figlio
    int somma = 0;      // Somma totale dei numeri restituiti dai figli

    // Creazione di 3 figli
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();     // Crea un nuovo processo

        if (pid < 0) {
            // Errore nella fork
            perror("Fork fallita");
            exit(1);
        }

        if (pid == 0) {
            // Codice del FIGLIO
            srand(time(NULL) + getpid());  // Seed random unico per ogni figlio
            int num = rand() % 101;        // Numero casuale tra 0 e 100
            printf("[Figlio PID=%d] Numero generato: %d\n", getpid(), num);
            exit(num);                     // Termina restituendo il numero
        }

        // Il padre continua il ciclo per creare altri figli
    }

    // Il padre attende la terminazione dei 3 figli
    for (int i = 0; i < 3; i++) {
        pid_t terminated_pid = wait(&wstatus);  // Bloccante: attende che un figlio termini

        if (WIFEXITED(wstatus)) {
            // Il figlio è terminato normalmente con exit()
            int exit_code = WEXITSTATUS(wstatus);  // Estrae il valore di exit()
            printf("[Padre] Figlio %d terminato con codice: %d\n", terminated_pid, exit_code);
            somma += exit_code;                    // Aggiungi il valore alla somma totale
        } else {
            // Il figlio è terminato in modo anomalo (es. segnale)
            printf("[Padre] Figlio %d terminato in modo anomalo\n", terminated_pid);
        }
    }

    // Output finale
    printf("[Padre] Somma totale dei risultati: %d\n", somma);

    return 0;
}