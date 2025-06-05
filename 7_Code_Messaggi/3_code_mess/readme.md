## Esercizio. Coda di messaggi con applicativi multipli

*Scrivere un’applicazione concorrente che sincronizzi tramite coda di messaggi UNIX tre tipologie di processi P1, P2, P3. I processi P1 e P2 inviano sulla coda un messaggio del tipo ``(PROCESS_ID, FLOAT_VALUE)``, dove il ``PROCESS_ID`` è la stringa ``"P1"`` o ``"P2"`` (a seconda del processo), mentre FLOAT_VALUE è un valore float generato casualmente nell'intervallo ``[i_dx,i_sx]``.
Il processo P3 dovrà ricevere 22 messaggi, 11 da parte del processo P1 e 11 dal processo P2, e calcolare la media cumulativa delle 2 serie. Al termine dei 22 messaggi ricevuti, il processo P3 stampa a video le medie calcolate. 

Compilare ed eseguire il codice:

```console
$ make
$ ./start
[START] Coda creata id=7

[P1] Avvio
[P2] Avvio

[P1] inviato: 91.2715
[P3] ricevuto  1/11 da P1: 91.2715
[P3] ricevuto  1/11 da P2: 35.3213

[P1] inviato:  5.6778
[P2] inviato: 60.0052
[P3] ricevuto  2/11 da P1:  5.6778
[P3] ricevuto  2/11 da P2: 60.0052
⋮
⋮               (output intermedio omesso per brevità)
⋮

[P1] inviato: 14.5696
[P3] ricevuto 11/11 da P1: 14.5696
[P3] ricevuto 11/11 da P2: 74.8677

=== RISULTATO FINALE ===
Media P1 (11 valori) = 41.0541
Media P2 (11 valori) = 51.3594

[P2] terminato
[P1] terminato
[START] Coda rimossa
```




