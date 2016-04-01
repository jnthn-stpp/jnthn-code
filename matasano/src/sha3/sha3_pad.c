#include "sha3.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void hash_pad(uint8_t ** str, int clen, int len){
  int add = len - (clen % len);
  uint8_t * temp = malloc((clen + add) * sizeof(uint8_t));
  memcpy(temp, (*str), clen);
  if(add == 1){
    temp[clen] = 0x86;
  } else if(add > 1){
    temp[clen] = 0x06;
    temp[clen + add - 1] = 0x80;
  }
  (*str) = temp;
}


void xof_pad(uint8_t ** str, int clen, int len){
  int add = clen % len;
  uint8_t * temp = malloc((clen + add) * sizeof(uint8_t));
  strncpy((*str), temp, clen);
  if(add == 1){
    temp[clen] = 0x9f;
  } else if(add > 1){
    temp[clen] = 0x1f;
    temp[clen + add - 1] = 0x80;
  }
  (*str) = temp;
}
