# Magazzino a **prenotazione**  
*(Monitor Hoare – signal & transfer)*

In questo esercizio il classico schema Produttore/Consumatore viene
reinterpretato come **clienti** che prelevano componenti e
**rifornitori** che li reintegrano, con un vincolo addizionale:
> almeno **uno slot** deve restare libero per consentire ai rifornitori di lavorare.

---

## 1 – Modello

| Slot | Stato            | Significato                                   |
|------|------------------|-----------------------------------------------|
| `LIBERO`     | 0 | pronto per essere prenotato da un cliente            |
| `PRENOTATO`  | 1 | lo sta usando un processo (cliente o rifornitore)    |
| `OCCUPATO`   | 2 | contiene un componente che può essere rimosso        |

Numero di slot `N_SLOTS = 3`.

### Processi

* **5 Clienti** – ognuno prenota uno slot libero, lavora 2 s, quindi
  conferma il prelievo (slot → `OCCUPATO`).
* **2 Rifornitori** – ognuno prenota uno slot `OCCUPATO`, esegue refill
  1 s, poi lo libera (slot → `LIBERO`).
* **Padre** – crea la shared memory con `Warehouse`, forka i figli e
  attende la terminazione.

---

## 2 – Strutture

```c
#define N_SLOTS 3
#define LIBERO     0
#define PRENOTATO  1
#define OCCUPATO   2

typedef struct {
    int stato[N_SLOTS];
    int liberi;                 /* # slot LIBERO        */
    int occupati;               /* # slot OCCUPATO      */
    Monitor m;                  /* monitor Hoare        */
} Warehouse;
```

## 3 - Output atteso
``` console
[CLI 3012] prenota slot 2
[CLI 3013] wait (solo 1 slot libero)
...
[RIF 3021] prenota slot 0
[CLI 3012] conferma slot 2 (OCCUPATO)
[RIF 3021] libera slot 0 (LIBERO)
[CLI 3013] riprende
```