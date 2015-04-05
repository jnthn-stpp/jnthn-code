cflags = -g

all : lib/libjnthn.a 

lib/libjnthn.a : bin/Stream.o bin/jnum.o
	ar rcs lib/libjnthn.a bin/Stream.o bin/jnum.o
bin/Stream.o : src/Stream.cpp include/Stream.h
	g++ -c src/Stream.cpp -o bin/Stream.o $(cflags)
	#cd tests; make StreamTest.exe
	#tests/StreamTest.exe
bin/jnum.o : src/jnum.cpp include/jnum.h
	g++ -c src/jnum.cpp -o bin/jnum.o $(cflags)

clean :
	-rm bin/Stream.o 
	-rm lib/libjnthn.a
	cd tests; make clean
