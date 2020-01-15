all: mqg main.o Queue.o

mqg: main.o Queue.o
	gcc -Wall -std=c99 -o mqg main.o Queue.o
main.o: main.c Queue.h
	gcc -Wall -std=c99 -c main.c Queue.c
Queue.o: Queue.c
	gcc -Wall -std=c99 -c Queue.c
clean:
	rm mqg Queue.o
