all: client server start

start: main.c
	gcc -o start main.c

client: client.c header.h
	gcc -o client client.c

server: server.o
	gcc -o server server.o -lpthread

server.o: server.c header.h
	gcc -c server.c -lpthread

clean:
	rm -f *.o client server start