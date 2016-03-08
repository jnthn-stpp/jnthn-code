#ifndef PAD_H
#define PAD_H
#include <stdint.h>

void pad_arb(uint8_t** src, int len, uint8_t fill);
void pad_narb(uint8_t** src, long clen, int len, uint8_t fill);

#endif
