#include "crypto.h"
#include <stdio.h>
#include <string.h>

char * pt = "1c0111001f010100061a024b53535009181c";
char * key = "686974207468652062756c6c277320657965";
int size;
int rsize;

int main(){
  
  size = strlen(pt);
  hexToraw(pt, size, &pt, &rsize);
  hexToraw(key, size, &key, &rsize);

  printf("plain text: %s \n", pt);
  printf("key: %s \n", key);
  
  xorEncode(pt, key, rsize, &pt, &rsize);
  printf("encoded raw: %s \n", pt);
  rawTohex(pt, rsize, &pt, &rsize);
  printf("encoded text: %s \n", pt);
  
}
