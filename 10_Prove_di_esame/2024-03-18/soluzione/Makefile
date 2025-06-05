all: start

start: start.o startRL startPL
	gcc -o start start.o

start.o: start.c header.h
	gcc -c start.c

startRL: mainRL.o procedure.o
	gcc -o startRL mainRL.o procedure.o -pthread

mainRL.o: mainRL.c header.h
	gcc -c mainRL.c

startPL: plotter.o procedure.o
	gcc -o startPL plotter.o procedure.o

procedure.o: procedure.c header.h
	gcc -c procedure.c

plotter.o: plotter.c header.h
	gcc -c plotter.c

clean: 
	rm -f *.o
	rm -f *~
	rm -f ./start
