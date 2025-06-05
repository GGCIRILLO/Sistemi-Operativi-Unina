#DEBUG = -DDEBUG_ 

all: main

main: main.o procedure.o monitor_hoare.o
	gcc -o main main.o procedure.o monitor_hoare.o

main.o: main.c procedure.h
	gcc -c -o main.o main.c

procedure.o: procedure.c procedure.h
	gcc -c -o procedure.o procedure.c

monitor_hoare.o: monitor_hoare.c monitor_hoare.h
	gcc -c -o monitor_hoare.o $(DEBUG) monitor_hoare.c

clean:
	rm -rf *.o
	rm -rf main