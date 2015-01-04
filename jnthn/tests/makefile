all: StreamTest

StreamTest: StreamTest.o ../bin/Stream.o ../include/Stream.h
	g++ -o StreamTest ../bin/Stream.o  StreamTest.o -lgtest -lpthread 
StreamTest.o: StreamTest.cpp
	g++ -c StreamTest.cpp 

clean: 
	-rm StreamTest
	-rm StreamTest.o
