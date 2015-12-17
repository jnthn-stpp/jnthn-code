cflags ?= -g
libdir = ../lib/
incldir = ../include/

all: StreamTest.exe StructTest.exe JNumTest.exe

StreamTest.exe: StreamTest.cpp ../bin/Stream.o ../include/Stream.h
	g++ -o StreamTest.exe StreamTest.cpp ../bin/Stream.o  -lgtest -lpthread $(cflags)
StructTest.exe: StructTest.cpp ../include/jstruct.h
	g++ -o StructTest.exe StructTest.cpp -lgtest -lpthread $(cflags)
JNumTest.exe : JNumTest.cpp ../include/jnum.h ../lib/libjnthn.a
	g++ -o JNumTest.exe JNumTest.cpp -I$(incldir) -L$(libdir) -ljnthn -lgtest -lpthread $(cflags)

clean: 
	-rm StreamTest.exe
	-rm StructTest.exe
	-rm JNumTest.exe
