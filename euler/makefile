libdir = ../jnthn/lib
incldir = ../jnthn/include

all : Problem4.exe Problem7.exe Problem9.exe Problem10.exe

Problem4.exe : Problem4.cpp $(libdir)/libjnthn.a
	g++ -I$(incldir) -L$(libdir) -o Problem4.exe Problem4.cpp -ljnthn 
Problem7.exe : Problem7.cpp $(libdir)/libjnthn.a
	g++ -I$(incldir) -L$(libdir) -o Problem7.exe Problem7.cpp -ljnthn 
Problem9.exe : Problem9.cpp
	g++ Problem9.cpp -o Problem9.exe
Problem10.exe : Problem10.cpp $(libdir)/libjnthn.a
	g++ -I$(incldir) -L$(libdir) -o Problem10.exe Problem10.cpp -ljnthn 

clean : 
	-rm Problem4.exe
	-rm Problem7.exe
	-rm Problem9.exe
	-rm Problem10.exe
