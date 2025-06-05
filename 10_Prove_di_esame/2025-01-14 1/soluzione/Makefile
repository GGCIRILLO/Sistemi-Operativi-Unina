start: start.c monitor_fifo.o monitor_signal_continue.o
	gcc -o start start.c monitor_fifo.o monitor_signal_continue.o

monitor_fifo.o: monitor_fifo.c monitor_fifo.h
	gcc -c monitor_fifo.c

monitor_signal_continue.o: monitor_signal_continue.c monitor_signal_continue.h
	gcc -c monitor_signal_continue.c

clean:
	rm -f start monitor_fifo.o monitor_signal_continue.o


