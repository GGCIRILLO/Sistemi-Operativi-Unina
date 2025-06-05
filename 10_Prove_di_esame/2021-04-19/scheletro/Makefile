all: auth

auth: main.o client.o server.o auth.o
	gcc -o auth  main.o client.o server.o auth.o

main.o: main.c auth.h
	gcc -c -o main.o main.c

client.o: client.c auth.h
	gcc -c -o client.o client.c

server.o: server.c auth.h
	gcc -c -o server.o server.c

auth.o: auth.c auth.h
	gcc -c -o auth.o auth.c

clean:
	rm -f *.o
	rm -f auth