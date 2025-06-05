# 🚀 Esercizio: Esecuzione di un comando con `exec()`

## 📚 Obiettivo

Scrivere un programma in linguaggio **C** che crei un **processo figlio** tramite `fork()` e, all'interno del figlio, utilizzi la **system call `exec()`** per eseguire un comando di sistema. Il processo padre dovrà attendere la terminazione del figlio e poi stampare un messaggio di completamento.

---

## 🧩 Specifiche

1. Il processo **padre** deve:
   - Creare un processo figlio con `fork()`
   - Stampare il proprio PID
   - Attendere la terminazione del figlio con `wait()`
   - Stampare un messaggio alla fine:  
     📌 `"Il figlio <PID> ha terminato."`

2. Il processo **figlio** deve:
   - Stampare il proprio PID
   - Eseguire il comando `ls -l` usando `execl()` oppure `execlp()`
   - Se la `exec()` fallisce, stampare un messaggio di errore con `perror()`

---

## 🎯 Obiettivo didattico

Questo esercizio aiuta a comprendere:

- La sequenza `fork()` → `exec()` → `wait()`
- Come `exec()` sostituisce il codice del processo
- Che `exec()` **non ritorna** se va a buon fine
- Il comportamento di padre e figlio in un'applicazione reale

---

## 🛠️ Suggerimenti tecnici

- Usa `execl("/bin/ls", "ls", "-l", NULL);` oppure  
  `execlp("ls", "ls", "-l", NULL);`
- Non dimenticare `#include <unistd.h>` e `#include <sys/wait.h>`
- Per gestire gli errori di `exec()`, verifica se ritorna `-1`

---

## 🖨️ Output atteso (esempio)
```
[Padre] PID = 12500
[Figlio] PID = 12501
<output del comando ls -l>
Il figlio 12501 ha terminato. ```