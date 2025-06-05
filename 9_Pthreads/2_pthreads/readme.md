# Esercizio Prodotto scalare “40 × 10 000” in parallelo

Esercizio di confronto tra elaborazione multiprocesso (IPC System V) e multithread (pthreads).

⸻

## Scopo

Calcolare il prodotto scalare di due vettori di 400 000 elementi (40 blocchi da 10 000) con due approcci :
| **File** | **Modello di parallelismo** | **Condivisione dati** |**Sincronizzazione**
|----------|----------------------------------|----------------------------|-------------------|
| **prodottoscalareMP.c** |40 processi creati con  fork()| Memoria condivisa System V | Semaforo System V
|**prodottoscalareMT.c** | 40 thread POSIX | Spazio di indirizzamento unico | Mutex POSIX

Il programma misura anche il **tempo di esecuzione** (micro-secondi) per confrontare le prestazioni dei due modelli.

## Struttura sorgenti

``` c
.
├── prodottoscalareMP.c   // versione multiprocesso
└── prodottoscalareMT.c   // versione multithread
```

## Esempio di output
``` console
Prodotto scalare =  400000.000000 
Tempo di esecuzione = 7641
```
*(l’ordine delle stampe nei due programmi può differire, e i micro-secondi dipendono dalla macchina)*