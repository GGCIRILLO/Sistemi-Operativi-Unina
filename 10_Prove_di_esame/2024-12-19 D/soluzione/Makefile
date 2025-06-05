all: client server start

start: main.c
	gcc -o start main.c

client: client.c header.h
	gcc -o client client.c

server: server.o procedure.o monitor_signal_continue.o
	gcc -o server server.o procedure.o monitor_signal_continue.o

server.o: server.c header.h
	gcc -c -o server.o server.c

procedure.o: procedure.c header.h
	gcc -c -o procedure.o procedure.c

monitor_signal_continue.o: monitor_signal_continue.c monitor_signal_continue.h
	gcc -c -o monitor_signal_continue.o monitor_signal_continue.c

clean:
	rm -f *.o client server start
