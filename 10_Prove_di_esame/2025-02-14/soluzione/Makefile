all: start server

start: main.o collettore.o sensore.o 
	gcc -o start main.o collettore.o sensore.o

main.o: main.c header_msg.h
	gcc -c main.c -o main.o

collettore.o: collettore.c header_msg.h
	gcc -c collettore.c -o collettore.o

sensore.o: sensore.c header_msg.h
	gcc -c sensore.c -o sensore.o

server: server.o semafori.o 
	gcc -o server server.o semafori.o

server.o: server.c semafori.h header_msg.h header_prodcons.h
	gcc -c server.c -o server.o

semafori.o: semafori.c semafori.h
	gcc -c semafori.c -o semafori.o

clean: objclean

objclean:
	rm -f *.o start server

