all: main client server

main: main.c
	gcc -o main main.c
	
server: server.o procedure.o
	gcc -o server server.o procedure.o -pthread
	
client: client.o procedure.o
	gcc -o client client.o procedure.o

client.o: header.h client.c
	gcc -c client.c

server.o: header.h server.c
	gcc -c server.c
	
procedure.o: header.h procedure.c
	gcc -c procedure.c

clean:
	rm -f main client server
	rm -f *.o
