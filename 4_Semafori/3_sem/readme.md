# 🧮 Esercizio 3 – Somma Totale con Processi & Semafori

## 📚  Descrizione

Il processo padre alloca un vettore di **10 000 interi** in **memoria condivisa
(System V)** e lo inizializza con valori casuali non negativi.  
Successivamente crea **10 processi figli**: ciascuno calcola la **somma
parziale** di una fetta di 1 000 elementi.  
Per accumulare il risultato globale, padre e figli condividono un **buffer
di 64 bit** (tipo `long long`) protetto da un **semaforo binario** di
mutua-esclusione.  
Al termine, il padre mostra:

* la somma totale,
* la media aritmetica (double),
* il tempo impiegato (facoltativo, bonus).

---

## 🎯  Obiettivi

1. **Padre**
   1. crea il vettore in shared memory e lo riempie con `rand() % 1000`,
   2. crea un buffer condiviso (`long long`) inizializzato a **0**,
   3. alloca un *set* con 1 semaforo binario (`mutex` = 1),
   4. genera 10 figli e ne attende la terminazione (`wait`),
   5. stampa somma totale e media (`totale / 10000.0`),
   6. rimuove semaforo e segmenti shared memory (`IPC_RMID`).

2. **Figli**  
   Per la propria porzione (1 000 valori) calcolano la somma parziale e aggiornano il buffer.

---

## ✅  Output atteso (esempio)

```bash
Figlio 23501: somma parziale = 505321
...
[PADRE] Somma totale  = 4 998 273
[PADRE] Media         = 499.8273