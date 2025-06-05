#include <stdio.h>      // per printf, fprintf, perror
#include <stdlib.h>     // per exit, atoi, etc.
#include <string.h>     // per strcmp, strncpy
#include <sys/ipc.h>    // per ftok, shmget
#include <sys/shm.h>    // per shmat, shmctl

#define SHM_SIZE 1024   // dimensione della memoria condivisa in byte

int main(int argc, char *argv[]) {
    // Verifica che almeno un argomento (modalità) sia stato passato
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <w|r|d> [stringa]\n", argv[0]);
        exit(1);
    }

    // 🔐 Genera una chiave unica per la SHM usando ftok()
    // Questo permette a processi diversi di condividere la stessa memoria
    key_t chiave = ftok(".", 'k');
    if (chiave == -1) {
        perror("Errore ftok");
        exit(1);
    }

    // === Modalità WRITE: scrive una stringa nella SHM ===
    if (strcmp(argv[1], "w") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Uso: %s w <stringa da scrivere>\n", argv[0]);
            exit(1);
        }

        // Crea la SHM se non esiste, altrimenti la recupera
        int ds_shm = shmget(chiave, SHM_SIZE, IPC_CREAT | 0664);
        if (ds_shm < 0) {
            perror("Errore shmget");
            exit(1);
        }

        // Collega il segmento SHM allo spazio di memoria del processo -> restituisce un puntatore usabile come normale vairabile
        char *p = (char *)shmat(ds_shm, NULL, 0);
        if (p == (void *)-1) {
            perror("Errore shmat");
            exit(1);
        }

        // Scrive la stringa nella SHM (limitata a 1023 caratteri)
        strncpy(p, argv[2], SHM_SIZE - 1);
        p[SHM_SIZE - 1] = '\0';  // Garantisce la terminazione della stringa

        printf("✅ Stringa scritta nella SHM: \"%s\"\n", p);
    }

    // === Modalità READ: legge e stampa il contenuto della SHM ===
    else if (strcmp(argv[1], "r") == 0) {
        // Accede alla SHM esistente (senza crearla - permessi 0664)
        int ds_shm = shmget(chiave, SHM_SIZE, 0664);
        if (ds_shm < 0) {
            perror("Errore shmget");
            exit(1);
        }

        // Collega la SHM per leggere il contenuto
        char *p = (char *)shmat(ds_shm, NULL, 0);
        if (p == (void *)-1) {
            perror("Errore shmat");
            exit(1);
        }

        // Stampa il contenuto letto dalla SHM
        printf("📥 Contenuto della SHM: %s\n", p);
    }

    // === Modalità DELETE: rimuove la SHM dal sistema ===
    else if (strcmp(argv[1], "d") == 0) {
        // Accede alla SHM esistente (non deve crearla)
        int ds_shm = shmget(chiave, SHM_SIZE, 0664);
        if (ds_shm < 0) {
            perror("Errore shmget");
            exit(1);
        }

        // Richiede al kernel di rimuovere il segmento SHM
        if (shmctl(ds_shm, IPC_RMID, NULL) == -1) {
            perror("Errore shmctl (IPC_RMID)");
            exit(1);
        }

        printf("🗑️ Shared memory eliminata con successo.\n");
    }

    // === Modalità non riconosciuta ===
    else {
        fprintf(stderr, "Modalità non riconosciuta: %s\n", argv[1]);
        exit(1);
    }

    return 0;
}