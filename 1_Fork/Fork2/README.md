# 🧮 Somma Concorrente Distribuita — Esercizio con `fork()`, `wait()` e `exit()`

## 📚 Descrizione

Scrivere un programma in linguaggio **C** che esegua una **somma concorrente** di segmenti di un array intero, usando **processi figli** creati con `fork()`. Ogni figlio calcola la somma di una porzione dell’array e la restituisce al padre tramite `exit()`.

---

## 🧩 Specifiche

### 👶 Parte 1: I figli
Il programma deve creare **N processi figli** (es. N = 4). Ciascun figlio:
- Calcola la somma di **una porzione dell’array** (uguale per tutti).
- Stampa il proprio **PID** e la **somma parziale** calcolata.
- Termina con `exit(somma % 256)`.

### 👨 Parte 2: Il padre
Il processo padre deve:
- Attendere la terminazione di ciascun figlio con `wait()`.
- Recuperare lo stato di terminazione (`wstatus`) e ottenere il valore di uscita tramite `WEXITSTATUS(wstatus)`.
- Stampare il **PID** e il **valore restituito** da ogni figlio.
- Sommare tutti i risultati e stampare la **somma totale**.

---

## 🧠 Dettagli implementativi

- L’array deve contenere **16 interi** inizializzati dal padre.
- L’array va diviso equamente in **N segmenti**.
  - Es: con N = 4 → 4 elementi per ciascun figlio.
- I limiti degli indici (`start`, `end`) vanno calcolati in base all’indice del ciclo `for` che crea i figli.

---

## ✍️ Suggerimenti tecnici

- Usare le librerie:
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <sys/wait.h>
  ```

---

## ⚠️ Note importanti

- `exit()` può restituire un valore massimo di **255** → usare `exit(somma % 256)` per evitare errori.
- Ogni figlio deve usare `getpid()` per stampare il proprio **PID**.
- Il padre deve usare le macro `WIFEXITED(wstatus)` e `WEXITSTATUS(wstatus)` per analizzare correttamente lo stato di terminazione dei figli.

---

## 🎓 Obiettivo didattico

Questo esercizio ha lo scopo di:

- ✅ Applicare la creazione di **processi multipli** tramite `fork()`.
- ✅ Comprendere il meccanismo di terminazione con `exit()` e **attesa con `wait()`**.
- ✅ Praticare l’elaborazione **concorrente e distribuita** su array e dati.
- ✅ Rinforzare l’uso corretto delle macro di sistema per interpretare lo **stato di terminazione dei processi figli**.

---

## 🖨️ Output atteso (esempio)

[Figlio PID=10234] Somma da indice 0 a 3 = 10
[Figlio PID=10235] Somma da indice 4 a 7 = 26
[Figlio PID=10236] Somma da indice 8 a 11 = 42
[Figlio PID=10237] Somma da indice 12 a 15 = 58

[Padre] Figlio 10234 terminato con codice: 10
[Padre] Figlio 10235 terminato con codice: 26
[Padre] Figlio 10236 terminato con codice: 42
[Padre] Figlio 10237 terminato con codice: 58

[Padre] Somma totale dei risultati: 136
