#ifndef XOR_H
#define XOR_H

void xorEncode(char * pt, char * key, int size, char ** out, int* nsize);

void xorLangDecode(char * pt, char** key, int keyNum, int size, char ** out, char** okey, int* score);
#endif
