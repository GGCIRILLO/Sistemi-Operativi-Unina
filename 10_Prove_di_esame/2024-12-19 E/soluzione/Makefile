all: start

start: procedure.o main.o monitor_signal_continue.o
	gcc -o start procedure.o main.o monitor_signal_continue.o

procedure.o: procedure.c header.h
	gcc -c -o procedure.o procedure.c

main.o: main.c header.h
	gcc -c -o main.o main.c

monitor_signal_continue.o: monitor_signal_continue.c monitor_signal_continue.h
	gcc -c -o monitor_signal_continue.o monitor_signal_continue.c

clean:
	rm -f start
	rm -f *.o