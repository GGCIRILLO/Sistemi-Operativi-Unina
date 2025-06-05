# ------------------------------------------------------------
# Makefile – Somma Totale con Processi & Semafori
# ------------------------------------------------------------

CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c99
LDFLAGS :=               # (vuoto: non servono librerie extra)

# eseguibile finale
TARGET  := somma_totale

# sorgenti / oggetti
SRC     := main.c processi-somma.c semafori.c
OBJ     := $(SRC:.c=.o)

# ------------------------------------------------------------
# regole principali
# ------------------------------------------------------------
.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# regola implicita per .o (override per aggiungere -c e -o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------------------------------------
# utility
# ------------------------------------------------------------
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)