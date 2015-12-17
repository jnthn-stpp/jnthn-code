all: cypher counter

jcode.o: jcode.c jcode.h
	gcc jcode.c -c
cypher: jcode.o cypher.c
	gcc cypher.c jcode.o -o cypher
counter: counter.c
	gcc counter.c -o counter
clean:
	-rm jcode.o
	-rm cypher
	-rm counter

