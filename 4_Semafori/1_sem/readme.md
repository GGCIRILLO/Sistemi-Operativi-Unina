## Esercizio 1.

In questo esercizio, si implementa una comunicazione inter-processo utilizzando una shared memory, disciplinando l'accesso con un semaforo. In particolare, si vuole creare 2 processi figli che incrementano per 100 volte una variable intera memorizzata nella shared memory.

Nei file [semafori.h](semafori.h) e [semafori.c](semafori.c) sono definite e implementate le operazioni di *wait* e *signal* su semaforo.

Nel file [main.c](main.c) è implementato il *main* del programma richiesto.

Alcune domande:

- Cosa succederebbe se eliminassi la chiamata a ``Wait_Sem()`` o a ``Signal_Sem()`` o a entrambi?
- Cosa indica il secondo parametro della ``semget()``?
- Cosa cambia utliizzando i flag ``IPC_CREAT | IPC_EXCL`` per la ``shmget()`` e la ``semget()``?


Provare a reimplementare questo esercizio su più eseguibili (basta utilizzare come chiave IPC la macro ``IPC_PRIVATE``?).


## Svolgimento

### Creazione risorse
- Ottieni un segmento di memoria condivisa grande quanto un int con shmget.
- Crea un set di un solo semaforo con semget (il secondo parametro, nsems, indica proprio il numero di semafori nel set).

### Collegamento e inzializzazione
- Collega il segmento al tuo processo con shmat, ottenendo un puntatore condiviso.
- Poni la variabile condivisa a 0.
- Inizializza il semaforo a 1 con semctl(... SETVAL), così diventa un mutex (1 = libero, 0 = occupato).

### Generazione figli
- Esegui due fork
- Ogni figlio eredita gli ID di memoria e semaforo

### Sezione Critica
- Per 100 iterazioni ciascuno:
	1.	esegui Wait_Sem (decremento: entra solo se il semaforo vale 1),
	2.	incrementa la variabile condivisa,
	3.	esegui Signal_Sem (incremento: libera il semaforo).

### Sincronizzazione finale
- Il padre fa wait() sui figli 
- Valore atteso : 200

### Pulizia risorse
- Rimuovi il segmento e il seto di semafori

## Domande
### Cosa succederebbe se eliminassi la chiamata a ``Wait_Sem()`` o a ``Signal_Sem()`` o a entrambi?
- Rimuovi ``Wait_Sem()``: Si verifica una race condition. Il valore finale del contatore sarà quasi sempre <200 e varierà ad ogni esecuzione.  Inoltre il semaforo viene solo incrementato (con Signal_Sem()), quindi il suo valore cresce senza controllo. Senza il "lock" (decremento a 0), nessuno controlla l'ordine di accesso; più processi leggono lo stesso valore prima che venga aggiornato.
- Rimuovi ``Signal_Sem()``:  Dead-lock immediato: il primo figlio che fa Wait_Sem() porta il semaforo da 1 a 0 e rimane dentro. Tutti gli altri tentativi di Wait_Sem() restano bloccati per sempre. Il programma non termina. Il semaforo non viene mai riportato a 1, quindi nessun altro processo riesce più ad acquisirlo. 
- Rimuovi entrambi:  Di nuovo race condition (risultato imprevedibile, < 200) ma niente dead-lock. Il semaforo resta a 1 perché nessuno lo tocca. La variabile è accessibile da tutti contemporaneamente; mancando anche Signal, il semaforo non viene alterato e l'esecuzione procede senza blocchi.

### Cosa indica il secondo parametro della ``semget()``?
Il secondo parametro, nsems, indica il numero di semafori nel set (nel nostro caso 1).

### Cosa cambia utliizzando i flag ``IPC_CREAT | IPC_EXCL`` per la ``shmget()`` e la ``semget()``?
Con IPC_CREAT la risorsa si crea e viene restituito l'ID esistente. Con IPC_EXCL, se la risorsa esiste già, verrà restituito un errore. In questo modo evitiamo ricicli involontari: se un segmento o un set di semafori è rimasto nel sistema da un’esecuzione precedente (magari terminata male), con IPC_EXCL lo scopri subito invece di usarlo inavvertitamente con dati sporchi.

### Provare a reimplementare questo esercizio su più eseguibili (basta utilizzare come chiave IPC la macro ``IPC_PRIVATE``?).
Vedi 1_sem_variante .