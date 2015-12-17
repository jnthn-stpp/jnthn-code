#include "key.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void keyRepeat(char *key, int size, int reps, char** dest, int *nsize){
  
  *nsize = size * reps;
  *dest = malloc(sizeof(char) * *nsize);
  
  for(int i = 0; i < reps; i++){
    memcpy(*dest + i*size*sizeof(char), key, size);
  }
}

char** asciiBlock(int length){
  char** out = malloc(128 * sizeof(char*));
  for(char i = 0; i < 127; i++){
    keyRepeat(&i, 1, length, &out[i], &length);
  }
  return out;
}
