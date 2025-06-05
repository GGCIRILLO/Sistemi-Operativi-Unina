all: start

start: main.o collettore.o sensore.o server.o
	gcc -o start main.o collettore.o sensore.o server.o -pthread

main.o: main.c header_msg.h
	gcc -c main.c -o main.o

collettore.o: collettore.c header_msg.h
	gcc -c collettore.c -o collettore.o

sensore.o: sensore.c header_msg.h
	gcc -c sensore.c -o sensore.o

server.o: server.c header_msg.h header_prodcons.h
	gcc -c server.c -o server.o

clean: ipcclean objclean

objclean:
	rm -f *.o start

ipcclean:
	ipcs -q | awk '($$2~/^[0-9]+$$/) { system("ipcrm -q " $$2) }'
