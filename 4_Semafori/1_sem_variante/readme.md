## Perché `ftok` è la chiave per usare **più eseguibili**

Nel primo esercizio avevamo un unico programma che:

1. creava la memoria condivisa e il semaforo con `IPC_PRIVATE`
2. eseguiva due `fork()`  
3. faceva usare a padre e figli gli **stessi** ID (ereditati dal processo‐padre).

Finché tutti i processi derivano dallo stesso eseguibile, `IPC_PRIVATE` funziona benissimo: la condivisione è garantita dalla **parentela** (gli ID di segmento e semaforo si propagano nell’albero dei `fork`).

---

### Il problema con eseguibili distinti

Se suddividiamo il progetto in più programmi, per esempio

- `setup`   → crea risorse  
- `worker`  → usa risorse  
- `clean`   → le rimuove

non c’è più ereditarietà di ID: ogni eseguibile è lanciato da **shell** o da **cron**, quindi ciascuna chiamata a

```c
shmget(IPC_PRIVATE, …)
semget(IPC_PRIVATE, …)

creerebbe risorse nuove e diverse. I processi non parlerebbero mai tra loro.

---

### Suddivisione in più eseguibili

Per testare davvero la logica “chiave condivisa + più processi indipendenti” conviene spezzare il vecchio `main.c` in **tre** programmi distinti:

| Programma | Responsabilità principale |
|-----------|---------------------------|
| **setup.c**   | Crea (o fallisce se già esistono) la shared-memory e il set di semafori, li inizializza a 0 / 1 e lancia due *worker*. |
| **worker.c**  | Apre le stesse risorse tramite `ftok`, esegue 100 `Wait/Signal` e incrementa la variabile. |
| **cleanup.c** | Apre le risorse con la stessa chiave e le rimuove con `IPC_RMID` (utile se un run va storto). |

Tutti e tre condividono **le stesse chiavi**:

```c
/* comuni a tutti i file */
#define FTOK_PATH   "."     /* qualsiasi path esistente                     */
#define PROJ_MEM    'M'     /* project-id per la memoria                    */
#define PROJ_SEM    'S'     /* project-id per il set di semafori            */