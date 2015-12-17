cflags = -std=c99 -g
libflags = -I ./include -L ./lib

default: lib/libcrypto.a

all: default all-tests

all-tests: tests/encode64 tests/fixed tests/sbxor tests/detectXor

lib/libcrypto.a : bin/data.o bin/xor.o bin/key.o bin/lang.o
	ar rcs lib/libcrypto.a bin/data.o bin/xor.o bin/key.o bin/lang.o

#object files
bin/data.o : include/data.h src/data.c
	gcc -c src/data.c -o bin/data.o $(cflags) $(libflags)
bin/lang.o : include/lang.h src/lang.c
	gcc -c src/lang.c -o bin/lang.o $(cflags) $(libflags)
bin/xor.o : include/xor.h src/xor.c include/lang.h src/lang.c
	gcc -c src/xor.c -o bin/xor.o $(cflags) $(libflags)
bin/key.o : include/key.h src/key.c
	gcc -c src/key.c -o bin/key.o $(cflags) $(libflags)


#test files
tests/encode64.o : tests/encode64.c
	gcc -c -o tests/encode64.o tests/encode64.c $(cflags) $(libflags)
tests/encode64 : lib/libcrypto.a tests/encode64.o
	gcc tests/encode64.o -lcrypto -o tests/encode64 $(cflags) $(libflags)
tests/fixed.o: tests/fixed.c
	gcc -c -o tests/fixed.o tests/fixed.c $(cflags) $(libflags)
tests/fixed : tests/fixed.o lib/libcrypto.a
	gcc tests/fixed.o -lcrypto -o tests/fixed $(cflags) $(libflags)
tests/sbxor.o : tests/sbxor.c
	gcc -c -o tests/sbxor.o tests/sbxor.c $(cflags) $(libflags)
tests/sbxor : tests/sbxor.o lib/libcrypto.a
	gcc tests/sbxor.o -lcrypto -o tests/sbxor $(cflags) $(libflags)
tests/detectXor.o : tests/detectXor.c
	gcc -c -o tests/detectXor.o tests/detectXor.c $(cflags) $(libflags)
tests/detectXor : tests/detectXor.o lib/libcrypto.a
	gcc tests/detectXor.o -lcrypto -o tests/detectXor $(cflags) $(libflags)

#clean commands
clean: clean-objects clean-tests clean-library

clean-objects:
	-rm bin/data.o
	-rm bin/xor.o

clean-tests:
	-rm tests/encode64
	-rm tests/encode64.o
	-rm tests/fixed
	-rm tests/fixed.o
	-rm tests/sbxor
	-rm tests/sbxor.o

clean-library:
	-rm lib/libcrypto.a
