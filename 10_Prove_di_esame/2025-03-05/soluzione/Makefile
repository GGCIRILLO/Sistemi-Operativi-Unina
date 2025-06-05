all: client server start

start: start.c header_msg.h
	gcc -o start start.c

client: client.c header_msg.h
	gcc -o client client.c

server: server.c header_msg.h header_prodcons.h prodcons.c
	gcc -o server server.c prodcons.c -pthread

clean:
	rm -f client server start