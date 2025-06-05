# 🧪 Esercizio Avanzato: Terminale di Monitoraggio con Starvation Alternata

## 🎯 Obiettivo

Simulare un sistema multiprocesso in cui:
- più processi **lettori** accedono a un terminale di monitoraggio (es. dashboard di stato),
- alcuni processi **scrittori** aggiornano ciclicamente lo stato del sistema.

In questo scenario, né i lettori né gli scrittori hanno priorità:  
🔁 ciò può causare **starvation alternata**, a seconda dell'ordine di esecuzione e concorrenza.

---

## 📋 Specifiche

### Memoria condivisa

Contiene:
- `status_code`: intero tra 0 e 9
- `diagnostic_message`: stringa (es. "OK", "FAIL", ecc.)
- `numlettori`, `numscrittori`: contatori di sincronizzazione

```c
typedef struct {
    int status_code;
    char diagnostic_message[32];
    int numlettori;
    int numscrittori;
} Monitor; 
```

## 🧠 Logica dei processi

### 🟢 Lettori (es. operatori)
• 2 processi lettori.
• Ciascuno legge:
    • lo status_code
	• e la diagnostic_message
• Simulano tempo di lettura con sleep(2)
• Eseguono 6 letture ciascuno

### 🔴 Scrittori (es. sistema automatico)
• 2 processi scrittori.
• Ciascuno esegue 3 aggiornamenti dello stato:
    • genera status_code ∈ [0, 9]
	• genera diagnostic_message casuale tra “OK”, “FAIL”, “WARN”, “BOOT”
• Simula scrittura con sleep(1)

## 🧪 Esempio di output atteso
```console
[Scrittore 1] Stato aggiornato: 4 - WARN
[Lettore 1] Stato letto: 4 - WARN
[Lettore 2] Stato letto: 4 - WARN
[Lettore 1] Stato letto: 4 - WARN
[Lettore 2] Stato letto: 4 - WARN
[Lettore 1] Stato letto: 4 - WARN
[Lettore 2] Stato letto: 4 - WARN
[Scrittore 1] Stato aggiornato: 7 - FAIL
[Scrittore 2] Stato aggiornato: 1 - OK
...
```
