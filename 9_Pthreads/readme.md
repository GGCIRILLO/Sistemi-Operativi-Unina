# Phtreads

## Che cosa sono i pthreads

pthreads (POSIX Threads) è lo standard definito da POSIX 1003.1 per la programmazione multithread in ambiente Unix-like (Linux, *BSD, macOS, ecc.).
Lo standard descrive un’API in linguaggio C che permette a un processo di creare più thread d’esecuzione che condividono lo stesso spazio di indirizzamento, gli stessi file descriptor e gran parte dello stato di processo, ma possiedono un proprio contesto di esecuzione (registri CPU, stack e contatore d’istruzione).

## Perché usarli

| **Obiettivo** | **Vantaggi principali** |
|------------------|----------------------|
| **Concorrenza I/O-bound** |Un thread può attendere disco/rete mentre altri continuano a elaborare.|
|**Parallelismo CPU-bound** | Su sistemi multi-core più thread eseguono realmente in parallelo.|
| **Semplicità di design (1 richiesta → 1 thread)** | Modello intuitivo per server web, proxy, RPC.|
| **Condivisione di memoria veloce** | Passaggio dati più leggero di IPC tra processi.|



## **Concetti di base dell’API** 
| **Funzione** | **Scopo essenziale** |
|-----------------|-------------------|
| `pthread_create` | Crea un nuovo thread e ne avvia la funzione start.|
| `pthread_join` | Attende il termine di un thread e ne raccoglie il valore di ritorno.|
| `pthread_exit` | Termina il thread corrente restituendo un valore a chi fa  join.
| `pthread_detach` | Rilascia risorse automaticamente quando il thread termina (no join).
| `pthread_cancel` |Richiede la cancellazione asincrona di un thread (con attenzione!).

### **Sincronizzazione**
| **Primitive** | **Uso tipico** |
|-----------------|--------------|
|**Mutex** (`pthread_mutex_t`)| Proteggere sezioni critiche da accessi concorrenti.
|**Condition variable** (`pthread_cond_t`)| Attesa di condizioni (producer/consumer).
|**Read-Write lock** (`pthread_rwlock_t`) | Molti lettori, un solo scrittore.
|**Barrier** (`pthread_barrier_t`) | Allineare un gruppo di thread a un punto comune.
 |**Spinlock** (`pthread_spinlock_t`) | Lock leggerissimo quando le attese sono brevissime.
|**Thread-local storage** (`pthread_key_t`) | Dati privati a ogni thread senza passare argomenti.
|**Una sola inizializzazione** (`pthread_once`) | Pattern singleton sicuro in presenza di più thread.

## Limiti e svantaggi
- Portabilità su Windows: non nativa (serve pthreads-win32 o tradurre verso WinAPI).
- Debug complesso: le corse di dati possono essere sottili e non deterministiche.
- Copia di stato condiviso: un bug in un thread può corrompere l’intero address-space del processo.
- Overhead di creazione: per task micro-secondi, meglio usare thread pool o tecnologie user-level (green threads, coroutine, async/await).

