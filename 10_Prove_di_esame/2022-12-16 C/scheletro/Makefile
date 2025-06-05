all: start sensore smistatore

start: main.c
	gcc -o start  main.c

sensore: sensore.c header.h
	gcc -o sensore sensore.c

smistatore: smistatore.c header.h
	gcc -o smistatore smistatore.c -lpthread

clean:
	rm -f *.o
	rm -f start
	rm -f sensore
	rm -f smistatore
