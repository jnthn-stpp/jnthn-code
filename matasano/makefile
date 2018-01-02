cflags = -std=c99 -fpic
libflags = -I ./include -L ./lib
phpflags = -I/usr/include/php/20151012 -I/usr/include/php/20151012/main -I/usr/include/php/20151012/TSRM -I/usr/include/php/20151012/Zend -I/usr/include/php/20151012/ext -I/usr/include/php/20151012/ext/date/lib
aesfiles = bin/aes/aes.o bin/aes/aes_ctr.o bin/aes/gf256.o bin/aes/matrix.o
sha3files = bin/sha3/keccak_f.o bin/sha3/sha3.o bin/sha3/sha3_pad.o bin/sha3/sha3_state.o bin/sha3/sha3_step.o bin/sha3/sponge.o
objfiles = bin/data.o bin/key.o bin/lang.o bin/pad.o bin/xor.o

#non-files
default:  lib/libaes.a lib/libsha3.a lib/libcrypto.a
all: default

swig: honors/demo.so
#libraries
lib/libcrypto.a : $(aesfiles) $(objfiles) $(sha3files)
	@echo -e "____________________________\nCrypto Library ...\c"
	@ar rcs lib/libcrypto.a $(objfiles) $(aesfiles) $(sha3files)
	@echo -e "\tdone\n"
lib/libsha3.a : $(sha3files) bin/data.o
	@echo -e "____________________________\nSHA3 Library ...\c"
	@ar rcs lib/libsha3.a $(sha3files) bin/data.o
	@echo -e "\tdone\n"
	@echo "SHA3 Unit Tests:"
	@cd tests; make -s sha3/sha3test; ./sha3/sha3test
	@echo ""; echo ""
lib/libaes.a : $(aesfiles) bin/data.o
	@echo -e "____________________________\nAES Library ...\c"
	@ar rcs lib/libaes.a $(aesfiles) bin/data.o
	@echo -e "\t\tdone\n"
	@echo "AES Unit Tests:"
	@cd tests; make -s aes/aestest; ./aes/aestest
	@echo ""; echo ""

#demo PHP module
honors/demo.so : bin/demo.o include/demo.h honors/demo_wrap.o
	gcc -shared bin/demo.o honors/demo_wrap.o -o honors/demo.so -lcrypto $(libflags)
honors/demo_wrap.o : honors/demo.i bin/demo.o
	swig -php honors/demo.i
	gcc -fpic -c honors/demo_wrap.c -o honors/demo_wrap.o $(phpflags)
bin/demo.o : src/demo.c include/demo.h
	gcc -c src/demo.c -o bin/demo.o -lcrypto $(cflags) $(libflags)
#object files
bin/data.o : include/data.h src/data.c
	@echo -e "Compiling data ...\c"
	@gcc -c src/data.c -o bin/data.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/lang.o : include/lang.h src/lang.c
	@echo -e "Compiling lang ...\c"
	@gcc -c src/lang.c -o bin/lang.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/xor.o : include/xor.h src/xor.c include/lang.h src/lang.c
	@echo -e "Compiling xor ...\c"
	@gcc -c src/xor.c -o bin/xor.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/key.o : include/key.h src/key.c
	@echo -e "Compiling key ...\c"
	@gcc -c src/key.c -o bin/key.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/aes/matrix.o : include/aes/matrix.h src/aes/matrix.c
	@echo -e "Compiling matrix ...\c"
	@gcc -c src/aes/matrix.c -o bin/aes/matrix.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/aes/aes.o : include/aes/aes.h src/aes/aes.c include/aes/matrix.h src/aes/matrix.c include/aes/gf256.h src/aes/gf256.c
	@echo -e "Compiling aes ...\c"
	@gcc -c src/aes/aes.c -o bin/aes/aes.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/aes/gf256.o : include/aes/gf256.h src/aes/gf256.c
	@echo -e "Compiling gf256 ...\c"
	@gcc -c src/aes/gf256.c -o bin/aes/gf256.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/pad.o : include/pad.h src/pad.c
	@echo -e "Compiling pad ...\c"
	@gcc -c src/pad.c -o bin/pad.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/aes/aes_ctr.o : include/aes/aes_ctr.h src/aes/aes_ctr.c
	@echo -e "Compiling aes_ctr ...\c"
	@gcc -c src/aes/aes_ctr.c -o bin/aes/aes_ctr.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/sha3/sha3_state.o : include/sha3/sha3_state.h src/sha3/sha3_state.c
	@echo -e "Compiling sha3_state...\c"
	@gcc -c src/sha3/sha3_state.c -o bin/sha3/sha3_state.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/sha3/sha3_step.o : include/sha3/sha3_step.h src/sha3/sha3_step.c
	@echo -e "Compiling sha3_step ...\c"
	@gcc -c src/sha3/sha3_step.c -o bin/sha3/sha3_step.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/sha3/keccak_f.o : include/sha3/keccak_f.h src/sha3/keccak_f.c
	@echo -e "Compiling keccak_f ...\c"
	@gcc -c src/sha3/keccak_f.c -o bin/sha3/keccak_f.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/sha3/sha3_pad.o : include/sha3/sha3_pad.h src/sha3/sha3_pad.c
	@echo -e "Compiling sha3_pad ...\c"
	@gcc -c src/sha3/sha3_pad.c -o bin/sha3/sha3_pad.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/sha3/sponge.o : include/sha3/sponge.h src/sha3/sponge.c
	@echo -e "Compiling sponge ...\c"
	@gcc -c src/sha3/sponge.c -o bin/sha3/sponge.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/sha3/sha3.o : include/sha3.h src/sha3/sha3.c
	@echo -e "Compiling sha3 ...\c"
	@gcc -c src/sha3/sha3.c -o bin/sha3/sha3.o $(cflags) $(libflags)
	@echo -e "\tdone"

#clean commands
clean: clean-objects clean-library clean-tests clean-aes clean-sha3 clean-swig

clean-objects:
	@echo -e "Cleaning Crypto Objects ...\c"
	-@rm $(objfiles) 2>/dev/null || true
	@echo -e "\tdone"
clean-aes:
	@echo -e "Cleaning AES Objects ...\c"
	-@rm $(aesfiles) 2>/dev/null || true
	@echo -e "\tdone"
clean-sha3:
	@echo -e "Cleaning SHA3 Objects ...\c"
	-@rm $(sha3files) 2>/dev/null || true
	@echo -e "\tdone"
clean-swig:
	@echo -e "Cleaning Swig Objects ...\c"
	-@rm honors/demo_wrap.o bin/demo.o honors/demo.so honors/demo.php 2>/dev/null || true
	@echo -e "\tdone"

clean-library:
	@echo -e "Cleaning Libraries ...\c"
	-@rm lib/libcrypto.a 2>/dev/null || true
	-@rm lib/libaes.a 2>/dev/null || true
	-@rm lib/libsha3.a 2>/dev/null || true
	@echo -e "\t\tdone"
clean-tests:
	@echo -e "Cleaning Tests ...\c"
	-@cd tests; make -s clean 2>/dev/null || true
	@echo -e "\t\tdone"
