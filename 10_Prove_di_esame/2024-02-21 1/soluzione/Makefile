all: start

start: main.o monitor.o procedure.o
	gcc -o start main.o monitor.o procedure.o

main.o: main.c header.h
	gcc -c main.c

monitor.o: monitor_hoare.c monitor_hoare.h
	gcc -c monitor_hoare.c -o monitor.o

procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	rm -f *.o start