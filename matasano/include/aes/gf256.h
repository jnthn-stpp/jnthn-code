#ifndef GF256_H
#define GF256_H
#include <stdint.h>

uint8_t gf256_mult(uint8_t a, uint8_t b);
uint16_t gf256_mod(uint16_t a, uint16_t b);
#endif
