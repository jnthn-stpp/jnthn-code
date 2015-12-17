#include "xor.h"
#include "lang.h"
#include <stdlib.h>
#include <stdio.h>

void xorEncode(char * pt, char * key, int size, char** out, int* nsize){
  (*nsize) = size;
  (*out) = malloc(size * sizeof(char));

  for(int i = 0; i < size; i++){
    (*out)[i] = pt[i] ^ key[i];
  }
}

void xorLangDecode(char* pt, char** key, int keyNum, int size, char** out, char** okey, int* score){
  xorEncode(pt, key[0], size, out, &size);
  *score = scoreText(*out, size);
  *okey = key[0];

  for(int i = 1; i < keyNum - 1; i++){
    char* cout;
    xorEncode(pt, key[i], size, &cout, &size);
    int cscore = scoreText(cout, size);

    if(cscore < *score){
      *score = cscore;
      *okey = key[i];
      *out = cout;
    } else {
      free(cout);
    }
  }
}
