incldir = ../jnthn/include
libdir = ../jnthn/lib
cflags = -g

calc.exe : main.cpp token.h fun.h calc.o
	g++ main.cpp calc.o -o calc.exe -I $(incldir) -L $(libdir) -ljnthn $(cflags)

calc.o : calc.cpp calc.h
	g++ calc.cpp -c -o calc.o -I $(incldir) -L $(libdir) -ljnthn $(cflags)

clean : 
	-rm calc.exe
	-rm calc.o
