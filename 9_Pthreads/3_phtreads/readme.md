
# **Produttori / Consumatori con** **pthreads**

_Esercizio di sincronizzazione tramite_ **_monitor_** _(mutex + condition variables)._

## **Obiettivo**
Simulare l’interazione tra  **produttori**  e  **consumatori**  che condividono un  _buffer_  di  **un solo elemento**  (mess).

Il progetto mostra come:
-   incapsulare il buffer dentro una struttura  **monitor**  (`struct ProdCons`);
-   proteggere la sezione critica con  `pthread_mutex_t`;
-   coordinare le due classi di thread mediante due  `pthread_cond_t`  (una per la produzione, una per il consumo).

## File Sorgenti
|**File** | **Ruolo** |
|----------|----------|
| **header.h** |Definisce il tipo di messaggio, la struttura del monitor e le firme delle funzioni.
| **procedure.c** |Implementa le operazioni del monitor (Inizio-/FineProduzione,  Inizio-/FineConsumo) e le  _start function_  di produttore/consumatore.
| **p_c_MT.c** | main  dell’esercizio: crea  **10 thread**  alternando produttori e consumatori, inizializza/distrugge le risorse e attende la terminazione.

## Logica del monitor

| **Variabile** | **Significato**  | **Valori possibili**
|-----------------|-------------------|----------------|
| `ok_produzione` | _È permesso produrre?_ | 1 = sì,  **0 = no**
| `ok_consumo` | _È permesso consumare?_ | 1 = sì,  **0 = no**

### **Flusso produttore**

1.  InizioProduzione
    
    _Lock_  sul mutex → attesa finché  ok_produzione == 1.
    
2.  Scrive il valore in  mess.
    
3.  FineProduzione
    
    -   set ok_produzione = 0, ok_consumo = 1;
        
    -   pthread_cond_signal(&ok_cons_cv);
        
    -   _Unlock_.
       
### **Flusso consumatore**

1.  InizioConsumo
    
    _Lock_  → attesa finché  ok_consumo == 1.
    
2.  Legge  mess.
    
3.  FineConsumo
    
    -   set ok_consumo = 0, ok_produzione = 1;
        
    -   pthread_cond_signal(&ok_prod_cv);
        
    -   _Unlock_.
        
Con un  **buffer a singolo slot**  l’invariante è: «in ogni istante o c’è  **esattamente un messaggio**  pronto da consumare, oppure il buffer è vuoto e si può produrre».


## Output atteso (esempio)
```console
Sono il thread Produttore, id 0
Sono il thread Consumatore, id 1
Thread #12345 Valore PRODOTTO = [345678]
Thread #12346, valore CONSUMATO = [345678]
...
Thread n.ro 9 terminato
```
Ogni thread produttore genera  **3 messaggi**  (timestamp in micro-secondi); ogni consumatore ne consuma 3, per un totale di 15 produzioni e 15 consumi.