cflags = -O2 

calc.exe : main.cpp token.h fun.h calc.o
	g++ main.cpp calc.o -o calc.exe $(cflags)

calc.o : calc.cpp calc.h
	g++ calc.cpp -c -o calc.o $(cflags)

clean : 
	-rm calc.exe
	-rm calc.o
