eseguibile: main.o monitor_hoare.o procedure.o
	gcc -o eseguibile main.o procedure.o monitor_hoare.o

main.o: main.c header.h
	gcc -c main.c -o main.o

monitor_hoare.o: monitor_hoare.c monitor_hoare.h
	gcc -c -o monitor_hoare.o  monitor_hoare.c

procedure.o: procedure.c header.h
	gcc -c procedure.c -o procedure.o

clean:
	rm -f *.o
	rm -f eseguibile
