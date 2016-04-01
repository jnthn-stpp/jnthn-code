cflags = -std=c99 -g
libflags = -I ../include -L ../lib -I ./unity -L ./unity
binary = encode64 fixed sbxor detectXor aesTrans aes_demo
aesobj = aes/test_aes.o aes/test_aes_ctr.o aes/test_gf256.o
sha3obj = sha3/test_sha3_state.o sha3/test_sha3_step.o sha3/test_sha3_main.o
all: aes/aestest sha3/sha3test

aes/test_aes.o : aes/test_aes.c ../src/aes/aes.c ../include/aes.h
	@gcc -c -o aes/test_aes.o aes/test_aes.c $(cflags) $(libflags)
aes/test_gf256.o : aes/test_gf256.c ../src/aes/gf256.c ../include/aes/gf256.h
	@gcc -c -o aes/test_gf256.o aes/test_gf256.c $(cflags) $(libflags)
aes/test_aes_ctr.o : aes/test_aes_ctr.c ../src/aes/aes_ctr.c ../include/aes/aes_ctr.h
	@gcc -c -o aes/test_aes_ctr.o aes/test_aes_ctr.c $(cflags) $(libflags)
aes/aestest : aes/test.c $(aesobj)
	gcc aes/test.c $(aesobj) -laes -lunity -o aes/aestest $(cflags) $(libflags)

sha3/test_sha3_state.o : sha3/test_sha3_state.c ../src/sha3/sha3_state.c ../include/sha3/sha3_state.h
	@gcc -c -o sha3/test_sha3_state.o sha3/test_sha3_state.c $(cflags) $(libflags)
sha3/test_sha3_step.o : sha3/test_sha3_step.c ../src/sha3/sha3_step.c ../include/sha3/sha3_step.h
	@gcc -c -o sha3/test_sha3_step.o sha3/test_sha3_step.c $(cflags) $(libflags)
sha3/test_sha3_main.o : sha3/test_sha3_main.c ../src/sha3/sha3.c ../include/sha3.h
	@gcc -c -o sha3/test_sha3_main.o sha3/test_sha3_main.c $(cflags) $(libflags)
sha3/sha3test : sha3/test_sha3.c $(sha3obj)
	gcc sha3/test_sha3.c $(sha3obj) -lsha3 -lunity -o sha3/sha3test $(cflags) $(libflags)

#test files
encode64.o : encode64.c
	gcc -c -o encode64.o encode64.c $(cflags) $(libflags)
encode64 : ../lib/libcrypto.a encode64.o
	gcc encode64.o -lcrypto -o encode64 $(cflags) $(libflags)
fixed.o: fixed.c
	gcc -c -o fixed.o fixed.c $(cflags) $(libflags)
fixed : fixed.o ../lib/libcrypto.a
	gcc fixed.o -lcrypto -o fixed $(cflags) $(libflags)
sbxor.o : sbxor.c
	gcc -c -o sbxor.o sbxor.c $(cflags) $(libflags)
sbxor : sbxor.o ../lib/libcrypto.a
	gcc sbxor.o -lcrypto -o sbxor $(cflags) $(libflags)
detectXor.o : detectXor.c
	gcc -c -o detectXor.o detectXor.c $(cflags) $(libflags)
detectXor : detectXor.o ../lib/libcrypto.a
	gcc detectXor.o -lcrypto -o detectXor $(cflags) $(libflags)
aesTrans.o : aesTrans.c ../lib/libcrypto.a
	gcc -c -o aesTrans.o aesTrans.c $(cflags) $(libflags)
aesTrans : aesTrans.o
	gcc aesTrans.o -lcrypto -o aesTrans $(cflags) $(libflags)
aes_demo.o : aes_demo.c ../lib/libcrypto.a
	gcc -c -o aes_demo.o aes_demo.c $(cflags) $(libflags)
aes_demo : aes_demo.o
	gcc aes_demo.o -lcrypto -o aes_demo $(cflags) $(libflags)

clean: clean-test

clean-test:
	-@rm $(aesobj) aes/aestest 2>/dev/null || true
	-@rm $(sha3obj) sha3/sha3test 2>/dev/null || true
clean-binary :
	-rm $(binary)
