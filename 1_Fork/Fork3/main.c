#include <stdio.h>      // printf()
#include <stdlib.h>     // exit(), rand(), srand()
#include <unistd.h>     // fork(), getpid(), sleep()
#include <sys/wait.h>   // wait(), WIFEXITED(), WEXITSTATUS()
#include <time.h>       // time()

#define N 5  // Numero di processi figli

int main() {
    int wstatus;             // Variabile per raccogliere lo stato dei figli
    int posizione = 1;       // Conta la posizione in classifica (ordine di arrivo)

    printf("=== INIZIO GARA ===\n");

    // Ciclo per creare i N figli
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();  // Crea un nuovo processo

        if (pid < 0) {
            perror("Fork fallita");
            exit(1);
        }

        if (pid == 0) {
            // === CODICE DEL FIGLIO ===

            // Inizializza il seed random (diverso per ogni figlio)
            srand(time(NULL) + getpid());

            // Genera un tempo casuale tra 1 e 5 secondi
            int rand_time = rand() % 5 + 1;

            // Simula il tempo di corsa
            sleep(rand_time);

            // Stampa il tempo impiegato
            printf("[Figlio PID=%d] Tempo impiegato: %d sec\n", getpid(), rand_time);

            // Termina restituendo il tempo come codice di uscita
            exit(rand_time);
        }

        // Il padre prosegue nel ciclo per generare gli altri figli
    }

    // === CODICE DEL PADRE ===
    // Attende ogni figlio (ordine casuale → simula ordine di arrivo)
    for (int i = 0; i < N; i++) {
        pid_t pid_terminato = wait(&wstatus);  // Attende la terminazione di un figlio

        if (WIFEXITED(wstatus)) {
            // Recupera il valore restituito dal figlio (tempo impiegato)
            int tempo = WEXITSTATUS(wstatus);

            // Stampa posizione in classifica
            printf("[Padre] %d° arrivato: Figlio PID=%d con tempo %d s\n",
                   posizione, pid_terminato, tempo);

            posizione++; // Incrementa la posizione
        } else {
            // Il figlio è terminato in modo anomalo (es. segnale)
            printf("[Padre] Figlio PID=%d terminato in modo anomalo\n", pid_terminato);
        }
    }

    printf("=== GARA CONCLUSA ===\n");
    return 0;
}