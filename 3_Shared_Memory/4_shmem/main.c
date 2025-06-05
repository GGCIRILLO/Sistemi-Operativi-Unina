#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit, rand, srand
#include <sys/ipc.h>    // ftok, shmget
#include <sys/shm.h>    // shmat, shmctl
#include <sys/wait.h>   // wait, WIFEXITED
#include <unistd.h>     // fork, getpid, sleep
#include <time.h>       // time()

#define N 5

// Struttura per memorizzare il risultato di ogni figlio
typedef struct {
    pid_t pid;
    int tempo;
} risultato_t;

// Struttura della SHM
typedef struct {
    risultato_t classifica[N];
    int index; // (non usato, ma presente per estensioni future)
} shm_data;

int main() {
    key_t k = ftok(".", 'k');
    if (k == -1) {
        perror("Errore in ftok");
        exit(1);
    }

    // Allocazione della memoria condivisa
    int ds_shm = shmget(k, sizeof(shm_data), IPC_CREAT | 0664);
    if (ds_shm < 0) {
        perror("Errore in shmget");
        exit(1);
    }

    // Attach alla SHM
    shm_data *dati = (shm_data *)shmat(ds_shm, NULL, 0);
    if (dati == (void *)-1) {
        perror("Errore in shmat");
        exit(1);
    }

    

    // === CREAZIONE DEI FIGLI ===
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Errore in fork");
            exit(1);
        }

        if (pid == 0) {
            // === CODICE DEL FIGLIO ===
            srand(time(NULL)+getpid());  // Inizializzazione del generatore random diverso per ogni figlio
            int num = rand() % 5 + 1; // tempo casuale tra 1 e 5
            sleep(num);               // simula tempo di gara

            // Scrive il risultato nella SHM
            dati->classifica[i].pid = getpid();
            dati->classifica[i].tempo = num;

            printf("[Figlio %d] PID=%d, tempo impiegato: %d secondi\n", i + 1, getpid(), num);

            // Uscita del figlio per evitare che continui il ciclo del padre
            exit(0);
        }
    }

    // === CODICE DEL PADRE ===
    int st;
    for (int i = 0; i < N; i++) {
        pid_t terminated = wait(&st);
        if (WIFEXITED(st)) {
            printf("[Padre] Figlio con PID=%d terminato correttamente\n", terminated);
        } else {
            printf("[Padre] Figlio terminato in modo anomalo\n");
        }
    }
    // Se voglio solo attendere senza stampare i log:
    // while (wait(NULL) > 0);  -> attende finché ci sono figli (se non conosco quanti figli)
    // for (int i = 0; i < N; i++) wait(NULL);

    // === ORDINAMENTO DEI RISULTATI === (Bubble sort semplice)
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (dati->classifica[j].tempo > dati->classifica[j + 1].tempo) {
                risultato_t temp = dati->classifica[j];
                dati->classifica[j] = dati->classifica[j + 1];
                dati->classifica[j + 1] = temp;
            }
        }
    }

    // === STAMPA CLASSIFICA FINALE ===
    printf("\n🏁 Classifica finale:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d° posto → PID %d (%d secondi)\n",
               i + 1, dati->classifica[i].pid, dati->classifica[i].tempo);
    }

    // Pulizia: rimozione SHM
    shmctl(ds_shm, IPC_RMID, NULL);
    printf("\n[Padre] Memoria condivisa rimossa. Fine.\n");

    return 0;
}