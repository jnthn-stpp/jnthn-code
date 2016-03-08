#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>

FILE* file;
char * pt;
char * et;
char ** keys;
int score;
int main(int argc, char** argv){
  file = fopen("xortest.txt", "r");
  if(!file){
    printf("File did not open");
  }
  score = 1000;
  keys = asciiBlock(30);
  for(int i = 0; i < 357; i++){
    int size = 60;
    int cscore;
    char * ckey;
    pt = malloc(60 * sizeof(char));
    fgets(pt, 60, file);
    //fgetc(file); //nl at end
    //printf("%s\n", pt);
    hexToraw(pt, size, &pt, &size);
    xorLangDecode(pt, keys, 128, size, &pt, &ckey, &cscore);
    if(cscore < score){
      et = pt;
      score = cscore;
      //printf("%s: score: %i\n", pt, cscore);
    }
  }
  printf("Decoded String: %s", et);
}
