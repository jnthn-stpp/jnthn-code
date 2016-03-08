#include "pad.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void pad_arb(uint8_t** src, int len, uint8_t fill){
  pad_narb(src, strlen(*src), len, fill);
}

void pad_narb(uint8_t** src, long clen, int len, uint8_t fill){
  int add;
  if(!(clen % len)){
    return;
  } else {
    add = len - (clen % len);
  }
  uint8_t * temp = malloc(sizeof(uint8_t) * (clen + add + 1));
  temp[clen + add] = 0x00;
  memset(temp, fill, clen + add);
  memcpy(temp, (*src), clen);
  //free(*src);
  (*src) = temp;
}
