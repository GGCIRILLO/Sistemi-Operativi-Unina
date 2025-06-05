# 🏁 Gara di Processi — `fork()`, `sleep()`, `exit()`, `wait()`

## 📚 Descrizione

Scrivere un programma in linguaggio **C** che simuli una **gara tra processi figli**. Ogni figlio partecipa alla corsa con una "velocità" casuale (simulata con `sleep()`), e il padre raccoglie i risultati nell'ordine di arrivo (terminazione).

---

## 🧩 Specifiche

### 👶 Ogni figlio deve:
- Attendere un tempo casuale tra **1 e 5 secondi** (`sleep()`).
- Stampare un messaggio con:
  - Il proprio **PID**
  - Il **tempo impiegato** (cioè quanto ha dormito)
- Terminare restituendo il tempo impiegato con `exit()`.

### 👨 Il padre deve:
- Creare **N figli** (es. N = 5)
- Attendere la terminazione di ciascun figlio con `wait()`
- Per ogni figlio terminato:
  - Stampare il **PID**
  - Il **tempo impiegato** (con `WEXITSTATUS`)
  - Il **posizionamento in classifica** (1°, 2°, …)

---

## ⚠️ Note importanti

- Usare `srand(time(NULL) + getpid())` nei figli per generare un seme casuale diverso.
- Usare `rand() % 5 + 1` per ottenere un valore tra 1 e 5 secondi.
- Ricordarsi che `exit()` accetta solo valori tra 0 e 255, quindi va bene per questo uso.
- Il padre non conosce a priori quanto tempo attende ogni figlio: l'ordine di `wait()` **simula l'arrivo**.

---

## 🖨️ Output atteso (esempio)
``` bash
[Figlio PID=12345] Tempo impiegato: 2 secondi
[Figlio PID=12346] Tempo impiegato: 5 secondi
[Figlio PID=12347] Tempo impiegato: 1 secondo
[Figlio PID=12348] Tempo impiegato: 3 secondi
[Figlio PID=12349] Tempo impiegato: 4 secondi

[Padre] 1° arrivato: Figlio PID=12347 con tempo 1 s
[Padre] 2° arrivato: Figlio PID=12345 con tempo 2 s
[Padre] 3° arrivato: Figlio PID=12348 con tempo 3 s
[Padre] 4° arrivato: Figlio PID=12349 con tempo 4 s
[Padre] 5° arrivato: Figlio PID=12346 con tempo 5 s
```

> 📝 **Nota**: L'ordine in cui appaiono i messaggi dei figli e del padre può sembrare "mischiato" o non ordinato.
> Questo comportamento è **del tutto normale e corretto**: i figli sono processi indipendenti che terminano e stampano
> in momenti diversi, in base al loro tempo di attesa (`sleep()`). L'ordine di stampa non è garantito, proprio perché
> riflette la **natura concorrente dei processi**.

---

## 🎓 Obiettivo didattico

Questo esercizio aiuta a comprendere:

- ✅ Come i processi si comportano in modo indipendente dopo una `fork()`.
- ✅ Uso di `sleep()` per simulare attività con durata variabile.
- ✅ Raccolta e ordinamento implicito dei risultati tramite `wait()` (ordine di arrivo).
- ✅ Utilizzo corretto di `exit()` e `WEXITSTATUS()` per comunicare valori tra processi.

