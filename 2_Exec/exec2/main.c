#include <stdio.h>      // printf, perror, fgets
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, execvp
#include <sys/wait.h>   // wait, WIFEXITED, WEXITSTATUS
#include <string.h>     // strtok, strcmp

#define MAX_INPUT 1024      // Lunghezza massima della riga di comando
#define MAX_ARGS 64         // Numero massimo di argomenti per il comando

int main() {
    char input[MAX_INPUT];     // Buffer per leggere la riga di input
    char* args[MAX_ARGS];      // Array di puntatori per i singoli argomenti

    printf("Avvio myshell...\n");

    while (1) {
        printf("myshell> ");
        fflush(stdout);  // Forza la stampa immediata del prompt

        // Legge la riga di input da tastiera 
        // fgets(buffer, size, stream) -> buffer è dove viene memorizzata, stream è da dove leggere
        if (fgets(input, MAX_INPUT, stdin) == NULL) { // "ls -l /home" -> "ls -l /home\n"
            printf("\nUscita dalla shell.\n");
            break; // EOF end of file (Ctrl+D) 
        }

        // Rimuove il newline finale (sostituisce '\n' con '\0')
        input[strcspn(input, "\n")] = '\0'; // "ls -l /home\n" -> "ls -l /home"

        // Se l'utente scrive "exit", termina la shell
        if (strcmp(input, "exit") == 0) {
            printf("Uscita dalla shell.\n");
            break;
        }

        // Suddivide la riga in token (parole) separati da spazi
        int argc = 0;
        char *token = strtok(input, " "); // "ls -l /home" -> "ls" , "-l", "/home",  NULL
        while (token != NULL && argc < MAX_ARGS - 1) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL; // Terminazione dell’array per execvp

        // Crea un nuovo processo figlio
        pid_t pid = fork();
        if (pid < 0) {
            // Se fork fallisce, stampa errore e riparte il ciclo
            perror("fork fallita");
            continue;
        }

        if (pid == 0) {
            // === CODICE DEL FIGLIO ===
            // Esegue il comando con i suoi argomenti 
            execvp(args[0], args); // execvp("ls", {"ls", "-l", "/home", NULL}); 

            // Se execvp fallisce, stampa errore e termina
            perror("exec fallita");
            exit(1);
        } else {
            // === CODICE DEL PADRE ===
            // Attende la terminazione del figlio
            int status;
            wait(&status);

            // Mostra il codice di uscita del figlio, se disponibile
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                printf("[Padre] Il comando è terminato con codice: %d\n", exit_code);
            } else {
                printf("[Padre] Il processo figlio non è terminato normalmente.\n");
            }
        }
    }

    return 0;
}