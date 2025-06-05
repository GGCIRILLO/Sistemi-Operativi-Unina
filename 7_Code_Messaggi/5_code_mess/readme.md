# 🚨 Centro Emergenze — code di messaggi System V

## 📚 Descrizione

Si vogliono simulare due “sorgenti di allarme” che inviano segnalazioni a un Centro Operativo.
Ogni sorgente è rappresentata da un processo - POLIZIA e METEO - che spedisce messaggi su unica coda di messaggi System V; il Centro Operativo è un terzo processo che riceve gli allarmi dando priorità a quelli della Polizia.

## 🧩 Specifiche

### ⚙️ Formati e costanti
```c
/* header.h */
#define FTOK_PATH "."           /* file esistente qualsiasi               */
#define MAX_TXT   64

#define MSG_POLIZIA  1          /* mtype per allarme di Polizia (prio alto) */
#define MSG_METEO    2          /* mtype per allarme Meteo   (prio basso)  */

struct alert {
    long  mtype;                /* deve essere long e primo campo         */
    char  text[MAX_TXT];        /* descrizione evento                     */
};
```

### 👮 Processo POLIZIA
- Invii totali: 8 messaggi
- Intervallo: Ogni 200 ms circa (usleep(200 000)).
- Contenuto: Stringhe casuali scelte fra:"Furto", "Aggressione", "Incendio", "Vandalismo".
- mtype : MSG_POLIZIA (== 1).
- Terminazione: Dopo l’ottavo messaggio spedisce il testo "FINE" e termina.

### 🌧️ Processo METEO
- Invii totali: 8 messaggi.
- Intervallo: Ogni 300 ms circa.
- Contenuto: Scelto fra:"Temporale", "Neve", "Nebbia", "Grandine".
- mtype: MSG_METEO (== 2).
- Terminazione: Dopo l’ottavo messaggio spedisce il testo "FINE" e termina.

### 🏢 Processo CENTRO OPERATIVO
- Obiettivo: Gestire 16 allarmi totali (8 Polizia + 8 Meteo).
- Strategia di ricezione: 
    1. Tenta sempre di prelevare un messaggio di tipo MSG_POLIZIA (alta priorità) con msgrcv(q, …, MSG_POLIZIA, 0).  2. Se non ne trova e il totale ricevuto < 16, preleva “il primo in coda” (msgtyp = 0).
- Output per ogni allarme: [CENTRO]  <timestamp>  <origine> : <testo>
- Al termine: Stampa il conteggio totale per ciascuna origine e chiude.

### 👨‍👩‍👧‍👦 Starter (padre)
1.	Crea la coda (msgget(IPC_PRIVATE, IPC_CREAT|0666)).
2.	fork() tre figli e li esegue (execl) come polizia, meteo, centro (passando l’ID di coda come argomento).
3.	Attende i figli (wait).
4.	Rimuove la coda con msgctl(…, IPC_RMID, NULL).

## ⚠️ Note importanti
•	Usare srand(time(NULL)+getpid()) per semi diversi nei due produttori.
•	I due produttori non devono creare la coda: la aprono con msgget(qkey, 0).
•	Per il Centro Operativo conviene contare quante volte msgrcv restituisce MSG_POLIZIA e quante MSG_METEO; termina quando la somma vale 16.
•	Ricordarsi di sottrarre sizeof(long) nel terzo parametro di msgsnd/msgrcv.

## 🖨️ Esempio di output (semplificato)
``` console
[POLIZIA] inviato: Furto
[POLIZIA] inviato: Vandalismo
[METEO]   inviato: Temporale
[POLIZIA] inviato: Aggressione
[METEO]   inviato: Nebbia
[...]

[CENTRO] 12:00:01  POLIZIA : Furto
[CENTRO] 12:00:01  POLIZIA : Vandalismo
[CENTRO] 12:00:01  POLIZIA : Aggressione
[CENTRO] 12:00:02  METEO   : Temporale
[CENTRO] 12:00:02  METEO   : Nebbia
[...]

=== STATISTICHE FINALI ===
Allarmi Polizia gestiti : 8
Allarmi Meteo   gestiti : 8
```
> 📝 Osservazione – L’ordine in cui i messaggi arrivano sul terminale riflette la scelta di priorità: finché esiste almeno un allarme “Polizia” in coda, viene servito prima di qualsiasi allarme “Meteo”.

