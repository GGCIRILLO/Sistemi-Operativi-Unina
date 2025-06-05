all: start client server database

start: start.c header.h
	gcc -o start start.c

client: client.c header.h
	gcc -o client client.c

server: server.c header.h
	gcc -o server server.c

database: database.c header.h
	gcc -o database database.c

clean:
	rm -f start client server database

