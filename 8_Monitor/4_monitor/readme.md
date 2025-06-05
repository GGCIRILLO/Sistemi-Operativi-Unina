# Lettori – Scrittori con **Monitor Hoare**

Esercizio che implementa il classico problema *Readers–Writers* usando un
**monitor con semantica Signal-and-Transfer (Hoare)**.  
L’obiettivo è consentire l’accesso **concorso** a più lettori, garantendo invece
l’**esclusione mutua** con gli scrittori **senza affamare** nessuna categoria.

## Semantica Hoare in breve
- Signal-and-Transfer: chi chiama signal_condition() cede subito il turno al processo risvegliato, finendo nella urgent queue.
- Il processo che riprende l’esecuzione trova la condizione già vera → basta if, non serve while(!cond).

## Fairness e assenza di starvation
1.	Gruppo di lettori
Ogni lettore riattiva il successivo lettore in coda ⇒ i lettori entrano a
blocchi, riducendo il numero di context-switch.
2.	Preferenza agli scrittori in coda
Quando uno scrittore esce, controlla prima se ci sono scrittori sospesi.
In tal modo, un flusso continuo di lettori non impedirà mai di scrivere.
3.	Semantica Hoare evita risvegli spuri e rende il controllo più prevedibile.