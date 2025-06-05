# Nome del compilatore
CC = gcc

# Nome del file sorgente
SRC = main.c

# Nome del file eseguibile
TARGET = shm_ex

# Flag di compilazione
CFLAGS = -Wall -g

# Regola principale
all: $(TARGET)

# Come costruire l'eseguibile
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Pulizia dei file generati
clean:
	rm -f $(TARGET)