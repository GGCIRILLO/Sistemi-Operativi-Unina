
# Sistemi Operativi – Esercizi e Prove d'Esame

> Università degli Studi di Napoli Federico II (Unina)  
> Anno: 2024-2025 - 
> Prof: Domenico Cotroneo

Questa repository raccoglie materiale organizzato per lo studio del corso di **Sistemi Operativi**, con particolare riferimento agli esempi trattati nella repository, esercizi svolti e prove d’esame risolte.

## Contenuto della repository

Ogni cartella numerata corrisponde a un argomento del corso. All’interno troverai:

- ✅ **Codici degli esempi del professore**, riscritti con **commenti dettagliati**.
- ✅ **README specifici** per spiegare il funzionamento e gli obiettivi del codice.
- ✅ **Esercizi del professore risolti**.
- ✅ **Esercizi inventati e risolti**, alcuni con **TODO** per tentare un’implementazione autonoma.
- ✅ **README** aggiunti per argomenti che non lo avevano nella repository originale del corso (es. **Monitor**, **Pthreads**).

---

## 📁 Struttura delle cartelle

### `1_Fork`
Gestione dei processi tramite `fork()`. Esempi sulla creazione di processi figli e sincronizzazione semplice.

### `2_Exec`
Uso della famiglia `exec()` per la sostituzione dell’immagine di processo (`execl`, `execvp`, ecc.).

### `3_Shared_Memory`
Creazione e utilizzo di **memoria condivisa** con le system call `shmget`, `shmat`, `shmctl`, ecc. Esempi e sincronizzazione tramite SHM.

### `4_Semafori`
Uso dei **semafori System V** per la sincronizzazione di processi. Pattern di cooperazione e competizione.

### `5_Prod_Cons`
Implementazione del problema classico **Produttore-Consumatore**, con buffer circolare, semafori e varianti.

### `6_Lett_Scritt`
Implementazioni del problema dei **Lettori e Scrittori**, con e senza starvation, usando semafori o monitor.

### `7_Code_Messaggi`
Utilizzo delle **code di messaggi UNIX** per la comunicazione asincrona tra processi. Pattern client-server e produttore-consumatore.

### `8_Monitor`
Esercizi basati sui **monitor** (signal-and-wait / signal-and-continue).  

### `9_Pthreads`
Introduzione ai **thread POSIX**, uso di `pthread_create`, `pthread_join`, mutex e condition variable.  

### `10_Prove_di_esame`
Circa **40 prove d’esame risolte**:
- Contengono uno **scheletro iniziale** e una **soluzione completa**, oltre alla traccia.
- Alcune includono spiegazioni strategiche per la risoluzione.
