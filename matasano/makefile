cflags = -std=c99 -g
libflags = -I ./include -L ./lib
aesfiles = bin/aes/aes.o bin/aes/aes_ctr.o bin/aes/gf256.o bin/aes/matrix.o
objfiles = bin/data.o bin/key.o bin/lang.o bin/pad.o bin/xor.o

#non-files
default:  lib/libaes.a lib/libcrypto.a
all: default
lib/libcrypto.a : $(aesfiles) $(objfiles)
	@echo -e "____________________________\nCrypto Library ...\c"
	@ar rcs lib/libcrypto.a $(objfiles) $(aesfiles)
	@echo -e "\tdone\n"
lib/libaes.a : $(aesfiles) bin/data.o
	@echo -e "____________________________\nAES Library ...\c"
	@ar rcs lib/libaes.a $(aesfiles) bin/data.o
	@echo -e "\t\tdone\n"
	@echo "AES Unit Tests:"
	@cd tests; make -s aes/aestest; ./aes/aestest
	@echo ""; echo ""

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

#clean commands
clean: clean-objects clean-library clean-tests clean-aes

clean-objects:
	@echo -e "Cleaning Crypto Objects ...\c"
	-@rm $(objfiles) 2>/dev/null || true
	@echo -e "\tdone"
clean-aes:
	@echo -e "Cleaning AES Objects ...\c"
	-@rm $(aesfiles) 2>/dev/null || true
	@echo -e "\tdone"

clean-library:
	@echo -e "Cleaning Libraries ...\c"
	-@rm lib/libcrypto.a 2>/dev/null || true
	-@rm lib/libaes.a 2>/dev/null || true
	@echo -e "\t\tdone"
clean-tests:
	@echo -e "Cleaning Tests ...\c"
	-@cd tests; make -s clean 2>/dev/null || true
	@echo -e "\t\tdone"
