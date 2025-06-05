CC = gcc
CFLAGS = -Wall -g

# Obiettivi
all: padre lettore scrittore

# Compilazione dei tre eseguibili principali
padre: padre.c semafori.o
	$(CC) $(CFLAGS) -o padre padre.c semafori.o

lettore: lettore.c semafori.o
	$(CC) $(CFLAGS) -o lettore lettore.c semafori.o

scrittore: scrittore.c semafori.o
	$(CC) $(CFLAGS) -o scrittore scrittore.c semafori.o

# Compilazione del modulo dei semafori
semafori.o: semafori.c semafori.h
	$(CC) $(CFLAGS) -c semafori.c

# Pulizia dei file compilati
clean:
	rm -f *.o padre lettore scrittore