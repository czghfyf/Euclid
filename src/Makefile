euclid: Euclid.o comm_proc.o
	gcc Euclid.o comm_proc.o -lpthread -o euclid

Euclid.o: Euclid.c command-processor.h
	gcc -c Euclid.c

comm_proc.o: command-processor.c command-processor.h
	gcc -c command-processor.c -o comm_proc.o

