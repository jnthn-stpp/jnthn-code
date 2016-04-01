#ifndef SPONGE_H
#define SPONGE_H
#include <stdint.h>

uint8_t * sha3_sponge(uint8_t * in, int len, int d);
  
#endif
