#ifndef SHA3_PAD_H
#define SHA3_PAD_H

#include <stdint.h>

void hash_pad(uint8_t ** str, int clen, int len);
void xof_pad(uint8_t ** str, int clen, int len);

#endif
