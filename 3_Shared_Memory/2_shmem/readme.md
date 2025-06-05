# 🧠 Esercizio: Memoria Condivisa (SHM) 

## 📚 Descrizione

Questo esercizio mostra come due processi (padre e figlio) possano **comunicare tramite memoria condivisa**.  
L’obiettivo è far capire i passaggi fondamentali dell’uso della SHM in modo semplice e isolato.

---

## 🧩 Funzionalità

- Il **padre** crea un segmento di memoria condivisa e vi scrive un valore intero.
- Il **figlio**, generato con `fork()`, accede allo stesso segmento e legge il valore.
- Il figlio stampa il valore letto.
- Il padre attende il figlio e poi rimuove la memoria condivisa.

---

## 🧪 Output atteso

Eseguendo il programma, otterrai qualcosa come:

```bash
[Padre] Scrivo il valore 42 nella SHM
[Figlio] Ho letto il valore: 42
[Padre] SHM rimossa