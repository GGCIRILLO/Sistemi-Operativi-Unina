prodcons: prodcons.o main.o monitor_signal_continue.o
	gcc -o prodcons prodcons.o main.o monitor_signal_continue.o

prodcons.o: prodcons.c prodcons.h
	gcc -c -o prodcons.o prodcons.c

main.o: main.c prodcons.h
	gcc -c -o main.o main.c

monitor_signal_continue.o: monitor_signal_continue.c monitor_signal_continue.h
	gcc -c -o monitor_signal_continue.o monitor_signal_continue.c

clean:
	rm -f prodcons
	rm -f *.o
