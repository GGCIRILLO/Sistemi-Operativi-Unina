#include <stdio.h>      // printf, perror, scanf
#include <stdlib.h>     // exit
#include <sys/ipc.h>    // ftok, shmget
#include <sys/shm.h>    // shmat, shmctl
#include <sys/wait.h>   // wait
#include <unistd.h>     // fork

int main() {
    // Genera una chiave unica per la SHM usando ftok
    key_t chiave = ftok(".", 'k');
    if (chiave == -1) {
        perror("Errore nella generazione della chiave con ftok");
        exit(1);
    }

    // Crea un segmento di memoria condivisa per contenere un intero
    int ds_shm = shmget(chiave, sizeof(int), IPC_CREAT | 0664);
    if (ds_shm < 0) {
        perror("Errore in shmget");
        exit(1);
    }

    // Collega il segmento SHM al processo e ottiene un puntatore
    int *p = (int *)shmat(ds_shm, NULL, 0);
    if (p == (void *)-1) {
        perror("Errore in shmat");
        exit(1);
    }

    // Chiedi all'utente un valore intero da scrivere
    int valore;
    printf("Inserisci un numero intero da scrivere nella SHM: ");
    scanf("%d", &valore);

    // Crea un processo figlio
    pid_t pid = fork();
    if (pid < 0) {
        perror("Errore nella fork");
        exit(1);
    }

    if (pid == 0) {
        // === CODICE DEL FIGLIO ===
        // Il figlio aspetta un attimo per dare tempo al padre di scrivere
        sleep(1);  // Non strettamente necessario, ma aiuta a sincronizzare
        printf("[Figlio] Ho letto il valore: %d\n", *p);
    } else {
        // === CODICE DEL PADRE ===
        // Scrive il valore ricevuto da input nella SHM
        *p = valore;
        printf("[Padre] Ho scritto il valore %d nella SHM\n", *p);

        // Attende la terminazione del figlio
        wait(NULL);

        // Rimuove la SHM dal sistema (pulizia)
        shmctl(ds_shm, IPC_RMID, NULL);
        printf("[Padre] SHM rimossa\n");
    }

    return 0;
}