#ifndef AES_CTR_H
#define AES_CTR_H
#include <stdint.h>

void icmt_ctr(uint8_t * block, uint8_t ** out, int num);
void aes_ctr_128(uint8_t * in, int len, uint8_t * block, uint8_t * key, uint8_t ** out);
void aes_ctr_192(uint8_t * in, int len, uint8_t * block, uint8_t * key, uint8_t ** out);
void aes_ctr_256(uint8_t * in, int len, uint8_t * block, uint8_t * key, uint8_t ** out);
#endif
