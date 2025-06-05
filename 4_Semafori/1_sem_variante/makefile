# ------------ variabili di compilazione ------------
CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c99

# ------------ target principali --------------------
all: setup worker cleanup

# ------------ regole di link -----------------------
setup: setup.o semafori.o
	$(CC) $(CFLAGS) -o $@ $^

worker: worker.o semafori.o
	$(CC) $(CFLAGS) -o $@ $^

cleanup: cleanup.o
	$(CC) $(CFLAGS) -o $@ $^

# ------------ regole di compilazione ---------------
setup.o: setup.c semafori.h
	$(CC) $(CFLAGS) -c $< -o $@

worker.o: worker.c semafori.h
	$(CC) $(CFLAGS) -c $< -o $@

cleanup.o: cleanup.c
	$(CC) $(CFLAGS) -c $< -o $@

semafori.o: semafori.c semafori.h
	$(CC) $(CFLAGS) -c $< -o $@

# ------------ pulizia ------------------------------
.PHONY: clean
clean:
	rm -f *.o setup worker cleanup