#include "sha3.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void xor_state(uint8_t * a, uint8_t * b, int size, uint8_t** out){
  (*out) = malloc(size * sizeof(char));

  for(int i = 0; i < size; i++){
    (*out)[i] = a[i] ^ b[i];
  }
}

uint8_t * sha3_sponge(uint8_t * in, int len, int d){
  int c = 2*d;
  int r = 200 - c;
  uint8_t * s = malloc(200 * sizeof(uint8_t));
  hash_pad(&in, len, r); //pad to 1600 bits (200 bytes)
  len += (r - (len % r));
  for(int i = 0; i < (len / r); i++){
    uint8_t * temp = malloc(200 * sizeof(uint8_t));
    for(int j = 0; j < r; j++){
      temp[j] = in[j];
    }
    xor_state(s, temp, 200, &s);
    s = keccak_f(s);
    in += r;
    //free(temp);
  }
  uint8_t * out = malloc(d * sizeof(uint8_t));
  for(int j = 0; j < d; j++){
    out[j] = s[j];
  }
  return out;
}
