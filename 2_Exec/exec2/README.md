# 🐚 Esercizio: Implementare una Unix Shell di base

## 📚 Descrizione

In questo esercizio andrai a implementare una semplice **shell Unix**, ovvero un interprete dei comandi simile a `bash` o `sh`.  
La shell dovrà essere **interattiva**: mostrerà un prompt, leggerà i comandi inseriti dall’utente, ed eseguirà i programmi richiesti tramite `fork()` e `exec()`.

---

## 🧩 Requisiti funzionali

Il programma deve:

1. Mostrare un **prompt** all’utente (es. `myshell>`)
2. Leggere una **riga di comando** da tastiera (`fgets`)
3. Dividere la riga in parole:
   - La **prima parola** è il comando da eseguire
   - Le successive sono i **parametri** del comando
4. Creare un **processo figlio** con `fork()`
5. Nel processo figlio:
   - Eseguire il comando richiesto con `execvp()`
6. Nel processo padre:
   - Attendere che il figlio termini con `wait()`
7. Dopo che il figlio termina, il ciclo ricomincia dal punto 1

---

## 🧠 Obiettivi didattici

- Comprendere come funziona una **shell Unix** a basso livello
- Saper gestire l’input utente e suddividerlo in comandi e argomenti
- Usare `fork()`, `execvp()` e `wait()` in maniera coordinata
- Consolidare l’uso della memoria (stringhe, array di puntatori) in C

---

## 🛠️ Suggerimenti tecnici

- Usa `fgets()` per leggere la riga da stdin
- Usa `strtok()` per separare le parole (token) in base agli spazi `" "`
- Usa `execvp()` per eseguire il comando (così non devi specificare il path completo)
- Termina la shell solo quando l’utente scrive `exit` o preme `Ctrl+D`

---

## 🖨️ Esempio di utilizzo

```bash
$ ./myshell
myshell> date
Thu Apr 18 15:22:43 CEST 2025
myshell> whoami
user42
myshell> ls -l
(total listing of current directory...)
myshell> exit
$