# Compilatore
CC = gcc

# Flag di compilazione
CFLAGS = -Wall -g

# File sorgente
SRC = main.c

# Nome eseguibile
TARGET = exec_example

# Regola principale
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Pulizia
clean:
	rm -f $(TARGET)