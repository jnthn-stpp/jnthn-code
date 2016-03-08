all : libunity.a

libunity.a : unity.o unity_fixture.o
	ar rcs libunity.a unity.o unity_fixture.o
unity.o : unity.c unity.h
	gcc -c -o unity.o unity.c
unity_fixture.o : unity_fixture.c unity_fixture.h unity_internals.h
	gcc -c -o unity_fixture.o unity_fixture.c
