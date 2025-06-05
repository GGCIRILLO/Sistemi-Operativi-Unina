# 🛠️ Esercizio Riepilogativo - Centro Stampa Universitario

## Obiettivo

Simulare un sistema multiprocesso che gestisce la stampa di documenti da parte di studenti e la raccolta delle stampe da parte degli addetti.

## Descrizione

- **30 processi studenti**: inviano documenti da stampare.
- **5 processi addetti**: raccolgono i documenti stampati e li archiviano.
- La comunicazione avviene tramite un **buffer circolare** di dimensione fissa.

## Funzionamento

- Ogni studente:
  - Genera un documento casuale (es. un numero intero tra 1000 e 9999).
  - Attende uno spazio libero nel buffer (se il buffer è pieno, si blocca).
  - Inserisce il documento nel buffer.
  - Termina.

- Ogni addetto:
  - Attende la presenza di un documento nel buffer (se il buffer è vuoto, si blocca).
  - Preleva il documento.
  - Simula il tempo di archiviazione (sleep(1)).
  - Stampa su schermo il documento archiviato.

## Strutture dati

Usare una memoria condivisa con la seguente struttura:

```c
#define DIM_BUFFER 10

typedef struct {
    int buffer[DIM_BUFFER];
    int testa;
    int coda;
} coda_stampa;

- testa: dove scrivono gli studenti.
- coda: da dove leggono gli addetti.


