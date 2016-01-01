cflags = -std=c99 -g
libflags = -I ./include -L ./lib
objfiles =  bin/data.o bin/xor.o bin/key.o bin/lang.o bin/matrix.o bin/aes.o bin/gf256.o

#non-files
default: lib/libcrypto.a
all: default all-tests
all-tests: tests/aesTrans tests/aes_demo
lib/libcrypto.a : $(objfiles)
	ar rcs lib/libcrypto.a $(objfiles)

#object files
bin/data.o : include/data.h src/data.c
	gcc -c src/data.c -o bin/data.o $(cflags) $(libflags)
bin/lang.o : include/lang.h src/lang.c
	gcc -c src/lang.c -o bin/lang.o $(cflags) $(libflags)
bin/xor.o : include/xor.h src/xor.c include/lang.h src/lang.c
	gcc -c src/xor.c -o bin/xor.o $(cflags) $(libflags)
bin/key.o : include/key.h src/key.c
	gcc -c src/key.c -o bin/key.o $(cflags) $(libflags)
bin/matrix.o : include/matrix.h src/matrix.c
	gcc -c src/matrix.c -o bin/matrix.o $(cflags) $(libflags)
bin/aes.o : include/aes.h src/aes.c
	gcc -c src/aes.c -o bin/aes.o $(cflags) $(libflags)
bin/gf256.o : include/gf256.h src/gf256.c
	gcc -c src/gf256.c -o bin/gf256.o $(cflags) $(libflags)



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
tests/aesTrans.o : tests/aesTrans.c lib/libcrypto.a
	gcc -c -o tests/aesTrans.o tests/aesTrans.c $(cflags) $(libflags)
tests/aesTrans : tests/aesTrans.o
	gcc tests/aesTrans.o -lcrypto -o tests/aesTrans $(cflags) $(libflags)
tests/aes_demo.o : tests/aes_demo.c lib/libcrypto.a
	gcc -c -o tests/aes_demo.o tests/aes_demo.c $(cflags) $(libflags)
tests/aes_demo : tests/aes_demo.o
	gcc tests/aes_demo.o -lcrypto -o tests/aes_demo $(cflags) $(libflags)

#clean commands
clean: clean-objects clean-tests clean-library

clean-objects:
	-rm $(objfiles)

clean-tests:
	-rm tests/encode64
	-rm tests/encode64.o
	-rm tests/fixed
	-rm tests/fixed.o
	-rm tests/sbxor
	-rm tests/sbxor.o
	-rm tests/aesTrans.o
	-rm tests/aesTrans

clean-library:
	-rm lib/libcrypto.a
