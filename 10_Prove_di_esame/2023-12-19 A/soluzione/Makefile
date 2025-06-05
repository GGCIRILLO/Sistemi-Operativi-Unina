all: main teatro report

main: main.o teatro report
	gcc -o main_exe main.o

main.o: main.c teatro.h
	gcc -c main.c

teatro: teatro.o teatro_procedure.o teatro.h
	gcc -o teatro teatro.o teatro_procedure.o -lpthread

teatro_procedure.o: teatro_procedure.c teatro.h
	gcc -c teatro_procedure.c

report: report.o teatro.h
	gcc -o report report.o

report.o: report.c teatro.h
	gcc -c report.c


clean:
	rm -f *.o 
	rm -f main_exe
	rm -f teatro
	rm -f report


