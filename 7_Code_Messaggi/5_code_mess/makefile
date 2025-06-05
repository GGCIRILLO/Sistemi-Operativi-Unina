CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
LDFLAGS =              # nessuna libreria esterna

SRC     = starter.c polizia.c meteo.c centro.c
OBJ     = $(SRC:.c=.o)
BIN     = starter polizia meteo centro

all: $(BIN)

starter: starter.o
	$(CC) $(CFLAGS) $^ -o $@

polizia: polizia.o
	$(CC) $(CFLAGS) $^ -o $@

meteo: meteo.o
	$(CC) $(CFLAGS) $^ -o $@

centro: centro.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean