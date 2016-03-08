cflags = -std=c99 -g
libflags = -I ./include -L ./lib
objfiles = bin/aes.o bin/aes_ctr.o bin/data.o bin/gf256.o bin/key.o bin/lang.o bin/matrix.o bin/pad.o bin/xor.o

#non-files
default: lib/libcrypto.a
all: default
lib/libcrypto.a : $(objfiles)
	@echo -e "____________________________\nPacking Library ...\c"
	@ar rcs lib/libcrypto.a $(objfiles)
	@echo -e "\tdone\n"
	@cd tests; make -s test; ./test

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
bin/matrix.o : include/matrix.h src/matrix.c
	@echo -e "Compiling matrix ...\c"
	@gcc -c src/matrix.c -o bin/matrix.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/aes.o : include/aes.h src/aes.c include/matrix.h src/matrix.c include/gf256.h src/gf256.c
	@echo -e "Compiling aes ...\c"
	@gcc -c src/aes.c -o bin/aes.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/gf256.o : include/gf256.h src/gf256.c
	@echo -e "Compiling gf256 ...\c"
	@gcc -c src/gf256.c -o bin/gf256.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/pad.o : include/pad.h src/pad.c
	@echo -e "Compiling pad ...\c"
	@gcc -c src/pad.c -o bin/pad.o $(cflags) $(libflags)
	@echo -e "\tdone"
bin/aes_ctr.o : include/aes_ctr.h src/aes_ctr.c
	@echo -e "Compiling aes_ctr ...\c"
	@gcc -c src/aes_ctr.c -o bin/aes_ctr.o $(cflags) $(libflags)
	@echo -e "\tdone"

#clean commands
clean: clean-objects clean-library clean-tests

clean-objects:
	@echo -e "Cleaning Objects ...\c"
	-@rm $(objfiles) 2>/dev/null || true
	@echo -e "\tdone"

clean-library:
	@echo -e "Cleaning Library ...\c"
	-@rm lib/libcrypto.a 2>/dev/null || true
	@echo -e "\tdone"
clean-tests:
	@echo -e "Cleaning Tests ...\c"
	-@cd tests; make clean
	@echo -e "\tdone"
