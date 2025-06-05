# Esercizio — “Hello World” multithread con pthreads

Benvenuto! Questo esercizio introduce le basi della programmazione multithread in C usando l’API POSIX Threads (pthreads).

⸻

## Contenuto del sorgente

```c
hello_threads.c          // codice dell’esercizio
```
Il programma:
1.	definisce una costante NUM_THREADS (qui = 5);
2.	nel main crea NUM_THREADS thread con pthread_create;
3.	ogni thread esegue la funzione PrintHello, che stampa un messaggio;
4.	il thread principale chiama pthread_exit(NULL) per restare vivo finché tutti i thread non terminano.

## Output atteso

```console
Creating thread 0
Creating thread 1
Creating thread 2
0: Hello World!
Creating thread 3
1: Hello World!
Creating thread 4
2: Hello World!
3: Hello World!
4: Hello World!
```