#ifndef AES_H
#define AES_H
#include <stdint.h>

/*
aes-128 input-16b output-16b key-16b
aes-192 input-16b output-16b key-24b
aes-256 input-16b output-16b key-32b
 */
void shiftRows(uint8_t *** state);
void mixColumns(uint8_t *** state);
void subBytes(uint8_t *** state);
void invShiftRows(uint8_t *** state);
void invMixColumns(uint8_t *** state);
void invSubBytes(uint8_t *** state);

void addRoundKey(uint8_t *** state, uint8_t * rkey);
void keySchedule(uint8_t * key, uint8_t ** out, int keylen, int rounds);

void aesEncrypt(uint8_t * in, uint8_t ** out, uint8_t * key, int rounds);
void aes_128_encrypt(uint8_t * in, uint8_t ** out, uint8_t * key);
void aes_192_encrypt(uint8_t * in, uint8_t ** out, uint8_t * key);
void aes_256_encrypt(uint8_t * in, uint8_t ** out, uint8_t * key);

void aesDecrypt(uint8_t * in, uint8_t ** out, uint8_t * key, int rounds);
void aes_128_decrypt(uint8_t * in, uint8_t ** out, uint8_t * key);
void aes_192_decrypt(uint8_t * in, uint8_t ** out, uint8_t * key);
void aes_256_decrypt(uint8_t * in, uint8_t ** out, uint8_t * key);


#endif
