all: start

start: main.c procedure.o 
	gcc -o start  main.c  procedure.o -lpthread

procedure.o: procedure.c header.h
	gcc -c -o procedure.o procedure.c

clean:
	rm -f start
	rm -f *.o