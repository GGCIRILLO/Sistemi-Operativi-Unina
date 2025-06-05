# Lettori – Scrittori con **Monitor Mesa** (Signal-and-Continue)

Questa cartella contiene la variante *Mesa* dell’esercizio lettori-scrittori.
La semantica **Signal-and-Continue** (detta anche *Mesa/Java*) differisce da
Hoare perché **lo scrittore che chiama `signal()` non cede subito il monitor**:
prosegue la sua procedura e libera il mutex solo in `leave_monitor()`.

---

## Fairness
1.	Priorità scrittori in coda
Quando uno scrittore termina, prima controlla queue_condition(SCRITTORI).
Se ci sono colleghi sospesi li sveglia—evita la starvation degli scrittori.
2.	Broadcast ai lettori
In assenza di scrittori in attesa lo scrittore esegue signal_all(LETTORI),
permettendo a tutti i lettori di accedere in gruppo.

Questo bilancia l’attesa e assicura che né lettori né scrittori restino
affamati.

**Perché signal_all sui lettori?**

Con Mesa, lo scrittore continua dopo la prima signal() anziché fermarsi.
Se si limitasse a svegliare un solo lettore, il resto dei lettori resterebbe
bloccato fino a un nuovo signal da parte di qualcun altro; perciò serve
un broadcast che rimetta in ready-queue l’intero gruppo.

(In Hoare bastava passare il testimone lettore→lettore con signal() singole,
perché ogni lettore attivato entrava immediatamente).