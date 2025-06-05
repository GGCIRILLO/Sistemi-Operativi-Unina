# ProdCons – **Pool di buffer** con Monitor (Signal-and-Continue)

Questo esercizio estende il caso “buffer 1” ai **buffer multipli** (`DIM > 1`)
mantenendo la semantica *Signal-and-Continue* (Mesa).  
Ogni slot del pool può trovarsi in uno di tre stati:

| Stato      | Significato                         |
|------------|-------------------------------------|
| `LIBERO`   | pronto per un nuovo dato            |
| `IN_USO`   | prenotato: il produttore/consumatore sta lavorando sul payload |
| `OCCUPATO` | pronto da consumare (dato valido)   |

Il monitor protegge **solo i metadati** (stato, contatori); l’elaborazione del
payload avviene fuori dal monitor per ridurre la sezione critica.

## Output esempio
```console 
Inizio consumatore
Ingresso monitor - consumazione
Sospensione - consumazione           ← nessun dato: si sospende
Inizio consumatore
Ingresso monitor - consumazione
Sospensione - consumazione
Inizio produttore
Ingresso monitor - produzione
Produzione - posizione 0, valore 2   ← primo slot
Uscita monitor - produzione
Produzione: 2
Riattivazione - consumazione         ← 1° consumatore riparte
Produzione - posizione 1, valore 6   ← il produttore riusa monitor
Uscita monitor - produzione
Produzione: 6
Riattivazione - consumazione         ← 2° consumatore riparte
Consumazione - posizione 0, valore 2
Uscita monitor - consumazione
Consumazione: 2
Consumazione - posizione 1, valore 6
Uscita monitor - consumazione
Consumazione: 6
```