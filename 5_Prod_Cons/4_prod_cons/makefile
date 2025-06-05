# Compilatore e flag
CC = gcc
CFLAGS = -Wall -g

# File oggetti comuni
OBJS = procedure.o semafori.o

# Target di default
all: clienti visualizzatore

# Compilazione dei file oggetto comuni
procedure.o: procedure.c procedure.h
	$(CC) $(CFLAGS) -c procedure.c

semafori.o: semafori.c semafori.h
	$(CC) $(CFLAGS) -c semafori.c

# Compilazione del programma clienti
clienti: clienti.c $(OBJS)
	$(CC) $(CFLAGS) -o clienti clienti.c $(OBJS)

# Compilazione del programma visualizzatore
visualizzatore: visualizzatore.c $(OBJS)
	$(CC) $(CFLAGS) -o visualizzatore visualizzatore.c $(OBJS)

# Pulizia dei file oggetti e degli eseguibili
clean:
	rm -f *.o clienti visualizzatore