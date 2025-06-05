  
  # Spooling di stampa con **aging** delle priorità  
*(Monitor Mesa – signal–and–continue)*

In questo esercizio estenderai il classico schema
produttore/consumatore con **tre livelli di priorità** e un meccanismo di
**aging**: se un job a bassa priorità resta troppo in coda,
“invecchia” e viene promosso a un livello superiore.

---

## 1 – Descrizione del problema

| Ruolo              | Processi | Attività                           |
|--------------------|----------|------------------------------------|
| **Printer**        | 1        | Consuma job di stampa da un heap, stampando in ordine di priorità (0 > 1 > 2). |
| **Utenti**         | 5        | Producono 5 job ciascuno:<br>• 1 utente *URGENTE* (prio 0), intervallo 2 s<br>• 2 utenti *NORMALE* (prio 1), intervallo 1 s<br>• 2 utenti *BASSA* (prio 2), intervallo 1 s |

*Il buffer è una **coda di priorità** (heap binario) di massimo 6 job.*

### Aging
Se un job di priorità **BASSA** attende **≥ 5 s** viene promosso a
priorità **NORMALE**.  
L’aging è implementato **dentro il monitor** ogni volta che
`get_next_job()` estrae un elemento.

---

## 2 – Strutture e API

```c
#define QUEUE_SIZE 6
#define PRIO_URG   0
#define PRIO_NORM  1
#define PRIO_LOW   2

typedef struct {
    int     id;          // PID dell’utente
    int     prio;        // 0,1,2 (può cambiare per aging)
    time_t  enqueue_ts;  // istante di inserimento
    int     pages;       // pagine da stampare
} print_job;

typedef struct {
    print_job heap[QUEUE_SIZE];
    int       count;     // # di job attualmente nel heap
    Monitor   m;         // monitor Mesa
} Spooler;
```

## **3 – Vincoli di sincronizzazione**

1.  **Produttori**  (submit_job) si bloccano se la coda è piena.
    
2.  **Printer**  (get_next_job) preleva l’elemento con priorità più
    
    alta; a parità di priorità, quello più vecchio.
    
3.  _Aging_  eseguito  **internamente**  al monitor:
    -  scansiona l’heap, promuove eventuali job  _LOW_  con 
       `time(NULL) - enqueue_ts >= 5`. 
      
## **4 - Output atteso**
```console
$ ./start
[P 28116] submit  URG  pages=1   (count=1)
[28155] Figlio Consumatore
[P 28117] submit  NORM pages=5   (count=2)

[C] dequeue URG  pid=28116 pages=1   (count=1)

[P 28119] submit  LOW  pages=10  (count=2)
[P 28118] submit  LOW  pages= 8  (count=3)
[P 28117] submit  NORM pages=4   (count=5)      

[C] dequeue NORM pid=28117 pages=5   (count=4)

[P 28120] submit  LOW  pages=5   (count=5)
[C] dequeue NORM pid=28118 pages=8   (count=5)

[P 28116] coda piena → wait           
…
[AGING] promote pid=28119  LOW→NORM   
[C] dequeue NORM pid=28119 pages=10   (count=5)
```
        