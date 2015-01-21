cflags ?= -g

all: StreamTest.exe

StreamTest.exe: StreamTest.cpp ../bin/Stream.o ../include/Stream.h
	g++ -o StreamTest.exe StreamTest.cpp ../bin/Stream.o  -lgtest -lpthread $(cflags)
clean: 
	-rm StreamTest.exe
