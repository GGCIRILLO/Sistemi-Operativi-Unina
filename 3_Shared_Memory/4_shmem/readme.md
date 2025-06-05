# 🏁 Gara a Eliminazione – Processi & Memoria Condivisa

## 📚 Descrizione

Questo esercizio simula una gara tra 5 processi figli. Ogni figlio ha un "tempo casuale di completamento", e i più lenti vengono eliminati. Solo i 3 più veloci entrano nella **classifica finale**, salvata nella memoria condivisa.

---

## 🎯 Obiettivo

- Ogni processo figlio simula una gara dormendo per un tempo casuale.
- Appena finisce, scrive nella shared memory il proprio PID e tempo impiegato.
- Il padre attende tutti i figli e costruisce la classifica ordinata per tempo.
- Stampa a video i 3 vincitori.

---

## 🛠️ Specifiche tecniche

- Usa `fork()` per generare 5 figli.
- Ogni figlio genera un tempo casuale tra 1 e 5 secondi (`rand()%5 + 1`)
- Ogni figlio:
  - Dorme per quel tempo
  - Scrive `PID` e `tempo` in un array di struct condiviso
- Il padre:
  - Attende tutti i figli
  - Ordina i risultati
  - Stampa i **3 più veloci**
- Usa `shmget`, `shmat`, `shmctl` e una `struct` per la SHM

---

## 📦 Struttura della SHM

```c
typedef struct {
    pid_t pid;
    int tempo;
} risultato_t;

typedef struct {
    risultato_t classifica[5];
    int index; // contatore atomico (gestito solo dai figli con cautela)
} shm_data;

## 🧪 Output atteso
``` bash
[Figlio 1 PID=43112] Tempo: 4s
[Figlio 2 PID=43113] Tempo: 2s
[Figlio 3 PID=43114] Tempo: 5s
[Figlio 4 PID=43115] Tempo: 1s
[Figlio 5 PID=43116] Tempo: 3s

🏆 Classifica finale:
1° posto → PID 43115 (1s)
2° posto → PID 43113 (2s)
3° posto → PID 43116 (3s)