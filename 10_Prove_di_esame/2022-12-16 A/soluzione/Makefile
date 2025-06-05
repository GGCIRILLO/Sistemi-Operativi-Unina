
all:  start

start: main.o semafori.o procedure.o
	gcc -g -o start main.c procedure.c semafori.c -lm
	
main.o: main.c semafori.h
	gcc -c -g -o main.o main.c

procedure.o: procedure.c semafori.h
	gcc -c -g -o procedure.o procedure.c
	
semafori.o: semafori.c semafori.h
	gcc -c semafori.c -o semafori.o

clean:
	rm -f *.o 
	rm -f ./start

