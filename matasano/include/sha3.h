#ifndef SHA3_H
#define SHA3_H

#include "sha3/sha3_pad.h"
#include "sha3/sha3_state.h"
#include "sha3/sha3_step.h"
#include "sha3/sponge.h"
#include "sha3/keccak_f.h"

uint8_t * sha3_224(uint8_t * in, int len);
uint8_t * sha3_256(uint8_t * in, int len);
uint8_t * sha3_384(uint8_t * in, int len);
uint8_t * sha3_512(uint8_t * in, int len);
#endif
