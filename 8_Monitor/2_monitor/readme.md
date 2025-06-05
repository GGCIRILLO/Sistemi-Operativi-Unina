# ProdCons – Monitor **Signal-and-Continue** (Mesa)

Questo esercizio è la **versione Mesa** del problema produttore/consumatore
con **buffer di dimensione 1**.  
È pensato per mettere a confronto due stili di monitor:

| Variante        | Esercizio | File monitor                |
|-----------------|-----------|-----------------------------|
| **Signal-and-Transfer** (Hoare) | 1 | `monitor_hoare.c` |
| **Signal-and-Continue** (Mesa)  | 2 | `monitor_signal_continue.c` |

---

## 1  Differenze chiave fra Hoare e Mesa

| Aspetto | Hoare (Signal-and-Transfer) | Mesa (Signal-and-Continue) |
|---------|-----------------------------|----------------------------|
| **Effetto di `signal()`** | Il thread risvegliato **entra subito** nel monitor; il segnalante va nella coda *urgent*. | Il segnalante **continua** la sua procedura e rilascia il monitor solo in `leave_monitor()`. |
| **Coda urgent** | Necessaria per conservare l’ordine: il segnalante attende lì. | **Assente**. |
| **Codice nei metodi del monitor** | Di solito basta `if`/`signal` (la condizione è garantita vera). | Obbligatorio il pattern `while (!cond) wait();` per ricontrollare la condizione al risveglio. |
| **Fairness / Starvation** | Più equo ma con costi di contesto maggiori. | Rischio di starvation se il thread risvegliato viene prevaricato da altri thread pronti. |
| **Implementazione** | Più complessa (mutex + urgent + counts). | Più semplice: solo mutex e array di condition. |

---

## 2  Struttura del progetto

.
├── main.c                       # test: crea produttori e consumatori
├── monitor_signal_continue.c    # implementazione del monitor Mesa
├── monitor_signal_continue.h
├── procedure.c                  # Produce() / Consuma() con WHILE
├── procedure.h
└── README.md                    # questo file

---

## 3  Come funziona la versione Mesa

### 3.1 Sequenza per il **produttore**

1. `enter_monitor(&m);`
2. `while (buffer_occupato) wait_condition(&m, VARCOND_PRODUTTORI);`
3. Scrive il dato, aggiorna gli stati.
4. `signal_condition(&m, VARCOND_CONSUMATORI);`
5. `leave_monitor(&m);`

> Il ciclo `while` è **obbligatorio**: fra il momento del `signal()` e il
> nostro risveglio un altro produttore potrebbe aver riempito di nuovo il buffer.

### 3.2 Logica del **monitor Mesa**

```text
wait_condition:
    ++cond_counts[id]
    V(mutex)              # libero il monitor
    P(cond_sem[id])       # mi sospendo
    P(mutex)              # lo ri-prendo

signal_condition:
    if (cond_counts[id] > 0)
        --cond_counts[id]
        V(cond_sem[id])   # sveglia UN thread (il segnalante non cede il turno)
```

## Punti di attenzione
- Ricontrollo del predicato: Usa sempre `while`, non `if`, su ogni `wait()`.
- Spurious wake-up: Alcuni kernel possono risvegliare un thread senza un vero `signal()`: il `while` protegge anche da questo.
- Starvation: Con molti thread la mancanza di coda urgent può far attendere a lungo chi è stato “signalled”. Valuta politiche di fairness (flag turno, contatori FIFO…).
- Pulizia risorse: Chiama `remove_monitor()` prima di `shmctl(..., IPC_RMID)` per non lasciare semafori orfani.
