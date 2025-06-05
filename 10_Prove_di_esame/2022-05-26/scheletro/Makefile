all: start

start: main.o prodcons.o monitor_hoare.o
	gcc -o start main.o prodcons.o monitor_hoare.o

main.o: main.c prodcons.h
	gcc -c -o main.o main.c

prodcons.o: prodcons.c prodcons.h monitor_hoare.h
	gcc -c -o prodcons.o prodcons.c

monitor_hoare.o: monitor_hoare.c monitor_hoare.h
	gcc -c -o monitor_hoare.o monitor_hoare.c

clean:
	rm -f start
	rm -f *.o