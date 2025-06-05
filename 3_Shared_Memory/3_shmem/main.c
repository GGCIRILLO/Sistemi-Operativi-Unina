#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit, rand, srand
#include <sys/ipc.h>    // ftok, shmget
#include <sys/shm.h>    // shmat, shmctl
#include <sys/wait.h>   // wait, WIFEXITED, WEXITSTATUS
#include <unistd.h>     // fork, getpid
#include <time.h>       // time()

int main() {
    key_t chiave = ftok(".", 'k');
    if (chiave == -1) {
        perror("Errore nella generazione della chiave con ftok");
        exit(1);
    }

    // Alloca spazio per 12 interi + 3 risultati (totale 15)
    int ds_shm = shmget(chiave, 15 * sizeof(int), IPC_CREAT | 0664);
    if (ds_shm < 0) {
        perror("Errore in shmget");
        exit(1);
    }

    // Collega la shm e ottiene un puntatore
    int *p = (int *)shmat(ds_shm, NULL, 0);
    if (p == (void *)-1) {
        perror("Errore in shmat");
        exit(1);
    }

    int N = 3; // Numero di figli
    int chunk_size = 4;
    int array[12];
    srand(time(NULL)); // Generatore casuale

    // Riempie array con valori casuali e stampa
    printf("[Padre] Array generato: ");
    for (int i = 0; i < 12; i++) {
        array[i] = rand() % 100 + 1;
        printf("%d ", array[i]);
        p[i] = array[i]; // Copia in SHM
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork fallita");
            exit(1);
        }

        if (pid == 0) {
            // === FIGLIO ===
            int temp = 0;
            int start = i * chunk_size;
            int end = start + chunk_size;

            for (int j = start; j < end; j++) {
                temp += p[j]; // legge dalla SHM
            }

            // Scrive il risultato nella parte finale della SHM
            p[12 + i] = temp;

            printf("[Figlio PID=%d] Somma [%d..%d]: %d\n", getpid(), start, end - 1, temp);
            exit(i + 1); // codice identificativo
        }
    }

    // === PADRE ===
    int wstatus;
    int somma_totale = 0;

    for (int i = 0; i < N; i++) {
        pid_t figlio = wait(&wstatus);
        if (WIFEXITED(wstatus)) {
            int id_logico = WEXITSTATUS(wstatus); // da 1 a 3
            int somma_parziale = p[12 + i]; // p[12], p[13], p[14]
            printf("[Padre] Ricevuto da figlio %d (PID %d): %d\n", id_logico, figlio, somma_parziale);
            somma_totale += somma_parziale;
        } else {
            printf("[Padre] Figlio terminato in modo anomalo.\n");
        }
    }

    printf("[Padre] Somma totale: %d\n", somma_totale);

    // Rimuove la SHM
    shmctl(ds_shm, IPC_RMID, NULL);
    printf("[Padre] SHM rimossa\n");

    return 0;
}