# ==========================================================
#  Makefile per il progetto “chat multiprocesso”
#  (main  = processo padre / orchestratore)
#  (sender = processo mittente)
#  (receiver = processo ricevente)
# ==========================================================

# --- impostazioni di compilazione --------------------------
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11
INCLUDES:= -I.               # header.h sta nella stessa directory

# --- eseguibili da generare --------------------------------
BINS := main sender receiver

# target di default
all: $(BINS)

# --- regole di compilazione/link ---------------------------
# ogni .o dipende dal rispettivo .c e da header.h
%.o: %.c header.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# link finale di ogni binario
main: main.o
	$(CC) $(CFLAGS) -o $@ $^

sender: sender.o
	$(CC) $(CFLAGS) -o $@ $^

receiver: receiver.o
	$(CC) $(CFLAGS) -o $@ $^

# --- pulizia dei file generati -----------------------------
clean:
	rm -f *.o $(BINS)

.PHONY: all clean
# ==========================================================