all: start client server

start: start.c header_msg.h
	gcc -o start start.c

client: client.c procedure.c header_msg.h header_sem.h
	gcc -o client client.c procedure.c

server: server.c procedure.c header_msg.h header_sem.h
	gcc -o server server.c procedure.c

clean:
	rm -f start client server