all: start

start: main.c procedure.o monitor_hoare.o semafori.o
	gcc -o start  main.c  procedure.o monitor_hoare.o semafori.o

procedure.o: procedure.c header.h
	gcc -c -o procedure.o procedure.c

monitor_hoare.o: monitor_hoare.c monitor_hoare.h
	gcc -c -o monitor_hoare.o monitor_hoare.c

semafori.o: semafori.c semafori.h
	gcc -c -o semafori.o semafori.c

clean:
	rm -f start
	rm -f *.o