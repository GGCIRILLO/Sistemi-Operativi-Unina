#include <stdio.h>      // printf()
#include <stdlib.h>     // rand(), srand(), exit()
#include <unistd.h>     // fork(), getpid()
#include <sys/wait.h>   // wait(), WIFEXITED(), WEXITSTATUS()
#include <time.h>       // time()

int main() {
    int wstatus;
    int N = 4;                  // Numero di figli
    int array[16];              // Array da suddividere tra i figli
    srand(time(NULL));          // Inizializza il generatore di numeri casuali (solo nel padre)

    // Inizializzazione dell'array con valori casuali tra 1 e 100
    for (int i = 0; i < 16; i++) {
        array[i] = rand() % 100 + 1;
    }

    // Stampa dell'array per controllo (facoltativa ma utile)
    printf("Array generato dal padre:\n");
    for (int i = 0; i < 16; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");

    int chunk_size = 16 / N;    // Quanti elementi deve sommare ogni figlio
    int sommaTot = 0;           // Somma finale raccolta dal padre

    // Creazione dei figli
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork fallita");
            exit(1);
        }

        if (pid == 0) {
            // Codice eseguito solo dal figlio
            int start = i * chunk_size;
            int end = start + chunk_size;

            int somma = 0;
            for (int j = start; j < end; j++) {
                somma += array[j];
            }

            // Il figlio stampa la somma calcolata
            printf("[Figlio PID=%d] Somma da indice %d a %d = %d\n",
                   getpid(), start, end - 1, somma);

            // Il figlio restituisce la somma tramite exit (modulo 256)
            exit(somma % 256);
        }

        // Il padre continua il ciclo e crea gli altri figli
    }

    // Codice eseguito solo dal padre: raccoglie i risultati
    for (int i = 0; i < N; i++) {
        pid_t terminated_pid = wait(&wstatus);  // Attende la terminazione di un figlio

        if (WIFEXITED(wstatus)) {
            int exit_code = WEXITSTATUS(wstatus);
            printf("[Padre] Figlio %d terminato con codice: %d\n", terminated_pid, exit_code);
            sommaTot += exit_code;
        } else {
            printf("[Padre] Figlio %d terminato in modo anomalo\n", terminated_pid);
        }
    }

    // Stampa finale della somma complessiva
    printf("\n[Padre] Somma totale dei risultati: %d\n", sommaTot);

    return 0;
}