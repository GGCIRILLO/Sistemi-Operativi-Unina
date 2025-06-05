all: reader server main

reader: reader.c header.h
	gcc -o reader reader.c

server: server.c header.h
	gcc -o server server.c -pthread

main: main.c
	gcc -o main main.c

clean:
	rm reader server main