#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>

FILE* file;
char * pt;
char * et;
char ** keys;
int score;
int main(int argc, char** argv){
  file = fopen(argv[1], "r");
  score = 1000;
  keys = asciiBlock(30);
  for(int i = 0; i < 357; i++){
    int size = 60;
    int cscore;
    char * ckey;
    pt = malloc(60 * sizeof(char));
    for(int j = 0; j < 60; j++){
      int tmp = fgetc(file);
    }
    fgetc(file); //nl at end
    hexToraw(pt, size, &pt, &size);
    xorLangDecode(pt, keys, 128, size, &pt, &ckey, &cscore);
    if(cscore < score){
      et = pt;
      printf("%s\n", pt);
    }
  }
  printf("Decoded String: %s", et);
}
