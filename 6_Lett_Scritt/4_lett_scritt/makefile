CC = gcc
CFLAGS = -Wall -O2
OBJ = main.o procedure.o semafori.o

all: programma

programma: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

main.o: main.c header.h semafori.h
	$(CC) $(CFLAGS) -c main.c

procedure.o: procedure.c header.h semafori.h
	$(CC) $(CFLAGS) -c procedure.c

semafori.o: semafori.c semafori.h
	$(CC) $(CFLAGS) -c semafori.c

clean:
	rm -f *.o programma