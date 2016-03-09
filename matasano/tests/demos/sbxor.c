#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * pt = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
int size;
int main(){
  size = strlen(pt);
  int cscore = 100000;
  char * ctext;
  char * ckey;
  int score;
  char ** keys;
  keys = asciiBlock(size);
  hexToraw(pt, size, &pt, &size);
  printf("Raw: %s \n", pt);
  xorLangDecode(pt, keys, 128, size, &pt, &ckey, &score);
  
  printf("Decoded raw: %s \n", pt);
  printf("Key: %c, Score: %i \n", ckey[0], score);
}
