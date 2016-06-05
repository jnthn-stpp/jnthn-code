#ifndef DEMO_H
#define DEMO_H
#include <stdint.h>

char * demo_aes_e(char * in, char * key);
char * demo_aes_d(char * in, char * key);
char * demo_sha3_224(char * in, int len);
char * demo_sha3_256(char * in, int len);
char * demo_sha3_384(char * in, int len);
char * demo_sha3_512(char * in, int len);
char * demo_counter(char * in, int num);
#endif
