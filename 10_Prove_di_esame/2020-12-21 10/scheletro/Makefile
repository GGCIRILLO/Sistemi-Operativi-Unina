all: main store updater viewer

main: main.o
	gcc -o main main.o

main.o: main.c header.h
	gcc -c main.c

store: store.o store_procedure.o store.h header.h
	gcc -o store store.o store_procedure.o

store_procedure.o: store_procedure.c store.h header.h
	gcc -c store_procedure.c

store.o: store.c store.h header.h
	gcc -c store.c

updater: updater.o header.h
	gcc -o updater updater.o

updater.o: updater.c header.h
	gcc -c updater.c

viewer: viewer.o header.h
	gcc -o viewer viewer.o

viewer.o: viewer.c header.h
	gcc -c viewer.c


clean:
	rm -f *.o 
	rm -f main
	rm -f store
	rm -f viewer
	rm -f updater


