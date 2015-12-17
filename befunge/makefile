cflags = -g

all: jbc makefile

jbc : main.o jstack.o
	gcc main.o jstack.o -o jbc $(cflags)
main.o : main.c
	gcc -c main.c -o main.o $(cflags)
jstack.o : jstack.c jstack.h
	gcc -c jstack.c -o jstack.o $(cflags)
clean:
	-rm main.o
	-rm jstack.o
	-rm jbc
