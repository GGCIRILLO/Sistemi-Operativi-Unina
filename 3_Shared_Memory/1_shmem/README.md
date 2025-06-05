# 🧠 shmtool – Strumento da linea di comando per memoria condivisa (SHM)

## 📚 Descrizione

`shmtool` è un semplice programma a linea di comando per gestire un'area di **memoria condivisa (shared memory)** tra processi.  
Permette di **scrivere**, **leggere** e **cancellare** una stringa memorizzata in una SHM.

---

## 🧩 Funzionalità

Il programma supporta tre modalità operative:

- `shmtool w <stringa>`  
  Scrive una stringa nella shared memory

- `shmtool r`  
  Legge e stampa il contenuto della shared memory

- `shmtool d`  
  Cancella la shared memory dal sistema

---

## 🧪 Esempio di utilizzo

```bash
# Scrittura
$ ./shmtool w "Ciao mondo"

# Lettura
$ ./shmtool r
Contenuto SHM: Ciao mondo

# Cancellazione
$ ./shmtool d
Shared memory eliminata con successo.