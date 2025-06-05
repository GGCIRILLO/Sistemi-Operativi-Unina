# Monitor Produttore – Consumatore (semantica Hoare)

Questo progetto mostra **come implementare un monitor Hoare in C** per risolvere il
problema produttore/consumatore con **buffer di dimensione 1**.  
Il monitor è realizzato “a mano” con semafori System V e memoria condivisa,
così da poterlo usare **anche fra processi** (e non solo fra thread).

---

## Punti di attenzione / trappole comuni

- Pulizia delle risorse: Alla fine main.c deve chiamare `remove_monitor()` prima di `shmctl(..., IPC_RMID)` oppure troverai semafori orfani.
- Semantica Hoare vs Mesa: Con Hoare la condizione è garantita vera al ritorno dalla `wait()` ↔ niente `while (!cond)`. 
- Ordine di creazione dei processi: Avviare prima i consumatori (e inserire un `sleep()` prima del produttore) dimostra che la `wait()` sospende correttamente.
- Uso di variabili di stato: `buffer_libero` / `buffer_occupato` devono essere aggiornate solo dentro il monitor.
- Priorità della coda urgent: `leave_monitor()` → se qualcuno è in urgent, risveglia lui e non rilascia il `mutex`; necessario per rispettare Hoare.
