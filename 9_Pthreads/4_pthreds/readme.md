# **Lettori / Scrittori con pthreads**

_Esercizio di sincronizzazione “Reader–Writer” basato su_ **_monitor_** _(mutex + condition variables)._

## **Scopo**
Gestire l’accesso concorrente a un  **buffer condiviso di un solo valore**  (mess) da parte di due categorie di thread:

-   **Scrittori**  – possono accedere  **in esclusiva**.
    
-   **Lettori**  – possono accedere  **in parallelo**  fra loro, purché non ci siano scrittori attivi.
     
Il monitor implementa  **priorità agli scrittori**  (evita la  _starvation_  degli scrittori).

## Strutture dei sorgenti
| **File** | **Ruolo**
|----------|----------
| **header.h**| Definisce il tipo di messaggio, la struttura del monitor  LettScritt  e le firme delle funzioni.
| **procedure.c** | Implementa il protocollo di ingresso/uscita dal monitor e le  _start function_  Scrittore  e  Lettore.
| **l_s_MT.c** | main  dell’esercizio: crea 10 thread alternando scrittori e lettori, inizializza/distrugge le risorse e attende il termine.

## **Disegno del monitor**
Variabili di stato (dentro  struct LettScritt):
| **Nome** | **Significato**
|-------------|----------
| `num_lettori` | Lettori  **attualmente**  dentro la sezione critica
| `num_scrittori` | Scrittori  **attualmente**  dentro
| `num_lettori_wait` | Lettori  **in attesa**  sulla CV
| `num_scrittori_wait` | Scrittori  **in attesa**  sulla CV

Condition variables:

-   `ok_lett_cv`  – lettori possono proseguire se  **nessuno scrittore attivo**.
    
-   `ok_scritt_cv`  – scrittori possono proseguire se  **nessun lettore né scrittore attivo**.
    
Algoritmo in breve:

1.  **InizioLettura**
    
    -   se c’è uno scrittore attivo ➜ il lettore incrementa  num_lettori_wait  e  _wait_;
        
    -   appena sicuro, incrementa  num_lettori  e rilascia il mutex (letture parallele).
        
    
2.  **FineLettura**
    
    -   decrementa  num_lettori;
        
    -   se diventa 0, sveglia  **un**  eventuale scrittore in attesa.
        
    
3.  **InizioScrittura**
    
    -   se ci sono lettori o scrittori attivi ➜ lo scrittore incrementa  num_scrittori_wait  e  _wait_;
        
    -   entra e pone num_scrittori = 1.
        
    
4.  **FineScrittura**
    
    -   azzera num_scrittori;
        
    -   se esistono scrittori in attesa ➜  signal  a uno di loro (priorità scrittori);
        
    -   altrimenti  broadcast  a tutti i lettori in attesa.
        

> **Nota**: dentro le funzioni di  _inizio_  il thread rilascia il mutex  **prima**  di eseguire la lettura/scrittura vera e propria: in questo modo altri thread possono mettersi in coda sulla CV evitando  _deadlock_.

## Output atteso (esempio)
```console
Sono il thread Scrittore (0)
Sono il thread Lettore (1)
Thread #12345 Valore SCRITTO = [456789]
Thread #12346, valore LETTO = [456789]
...
Thread n.ro 9 terminato
```
