#include "sha3.h"

uint8_t * sha3_224(uint8_t * in, int len){
  uint8_t * out = sha3_sponge(in, len, 28);
  return out;
}
uint8_t * sha3_256(uint8_t * in, int len){
  uint8_t * out =  sha3_sponge(in, len, 32);
  return out;
}
uint8_t * sha3_384(uint8_t * in, int len){
  uint8_t * out =  sha3_sponge(in, len, 48);
  return out;
}
uint8_t * sha3_512(uint8_t * in, int len){
  uint8_t * out =  sha3_sponge(in, len, 64);
  return out;
}
