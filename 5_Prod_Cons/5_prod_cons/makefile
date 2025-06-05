CC = gcc
CFLAGS = -Wall -g

OBJS = procedure.o semafori.o

all: studenti addetti

procedure.o: procedure.c procedure.h semafori.h
	$(CC) $(CFLAGS) -c procedure.c

semafori.o: semafori.c semafori.h
	$(CC) $(CFLAGS) -c semafori.c

studenti: studenti.c $(OBJS) procedure.h semafori.h
	$(CC) $(CFLAGS) -o studenti studenti.c $(OBJS)

addetti: addetti.c $(OBJS) procedure.h semafori.h
	$(CC) $(CFLAGS) -o addetti addetti.c $(OBJS)

clean:
	rm -f *.o studenti addetti