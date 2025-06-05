all: main_ex

main_ex: main.o procedure.o
	gcc -o main_ex main.o procedure.o

main.o: main.c header.h
	gcc -c main.c

procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	rm -rf main_ex
	rm -rf *.o
