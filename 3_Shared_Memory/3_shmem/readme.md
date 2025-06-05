# 🧠 Somma distribuita con processi e memoria condivisa

## 📚 Descrizione

Questo esercizio riassume tutto ciò che hai imparato: creazione di processi, comunicazione tramite memoria condivisa, e sincronizzazione con `wait()`.

Il programma:
1. Alloca una memoria condivisa per contenere un array di 12 interi e le somme.
2. Il padre genera 3 figli con `fork()`.
3. Ogni figlio:
   - Somma una porzione dell'array (4 elementi ciascuno).
   - Scrive il proprio risultato in memoria.
   - Termina restituendo il proprio ID logico (1, 2 o 3).
4. Il padre attende i figli e calcola la somma totale leggendo i risultati.
5. Alla fine stampa:
   - Le somme parziali di ciascun figlio
   - La somma totale
   - Rimuove la SHM

---

## 📦 Obiettivi didattici

- Applicare `fork()` e `wait()` in modo controllato
- Usare la `shared memory` per comunicare valori tra processi
- Sincronizzare correttamente padre e figli
- Gestire strutture dati in SHM (array, variabili multiple)

---

## 🛠️ Struttura della SHM

La SHM conterrà:
- `int array[12]` → dati di input
- `int risultati[3]` → somme parziali scritte dai figli 

Totale: almeno `(12 + 3) * sizeof(int)` → ~60 byte

> Nota: la somma totale viene calcolata dal padre, quindi non c'è bisogno di memorizzarla
---

## ▶️ Esecuzione attesa

> Nota; l'ordine potrebbe essere sfalsato, dato che sono processi concorrenti

```bash
$ ./shm_sum
[Padre] Array generato: 87 44 96 30 2 89 68 63 19 72 47 90
[Figlio PID=14203] Somma [0..3]: 257
[Figlio PID=14204] Somma [4..7]: 222
[Figlio PID=14205] Somma [8..11]: 228
[Padre] Ricevuto da figlio 1 (PID 14203): 257
[Padre] Ricevuto da figlio 2 (PID 14204): 222
[Padre] Ricevuto da figlio 3 (PID 14205): 228
[Padre] Somma totale: 707
[Padre] SHM rimossa
