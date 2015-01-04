all : lib/libjnthn.a 

lib/libjnthn.a : bin/Stream.o
	ar rcs lib/libjnthn.a bin/Stream.o
bin/Stream.o : src/Stream.cpp include/Stream.h
	g++ -c src/Stream.cpp -o bin/Stream.o
	cd tests; make StreamTest
	tests/StreamTest

clean :
	rm bin/Stream.o 
	rm lib/libjnthn.a
	cd tests; make clean
