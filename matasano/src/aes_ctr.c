#include "aes_ctr.h"
#include "crypto.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


void icmt_step(uint8_t * block, uint8_t ** out){
  (*out) = malloc(16 * sizeof(uint8_t));
  memcpy((*out), block, 16);
  for(int j = 15; j >= 0; j--){
    (*out)[j] = block[j] + 1;
    if((*out)[j] > block[j]){
      break;
    }
  }
}

void icmt_ctr(uint8_t * block, uint8_t ** out, int num){
  uint8_t * temp = block;
  for(int i = 0; i < num; i++){
    icmt_step(temp, out);
    temp = (*out);
  }
}

void aes_ctr_128(uint8_t * in, int ilen, uint8_t * block, uint8_t * key, uint8_t ** out){
  uint8_t * ctr_block = block;

  uint8_t * pad;
  (*out) = malloc(ilen * sizeof(uint8_t));
  
  for(int i = 0; i < ilen/16; i++){
    uint8_t * i_ptr = in + 16*i;
    uint8_t * o_ptr = malloc(sizeof(uint8_t) * 16);
    aes_128_encrypt(ctr_block, &pad, key);
    xorEncode(i_ptr, pad, 16*sizeof(uint8_t), (char **) &o_ptr);
    memcpy((*out) + 16*i, o_ptr, 16);
    icmt_ctr(ctr_block, &ctr_block, 1);
  }
}

void aes_ctr_192(uint8_t * in, int ilen, uint8_t * block, uint8_t * key, uint8_t ** out){
  uint8_t * ctr_block = block;

  uint8_t * pad;
  (*out) = malloc(ilen * sizeof(uint8_t));
  
  for(int i = 0; i < ilen/16; i++){
    uint8_t * i_ptr = in + 16*i;
    uint8_t * o_ptr = malloc(sizeof(uint8_t) * 16);
    aes_192_encrypt(ctr_block, &pad, key);
    xorEncode(i_ptr, pad, 16*sizeof(uint8_t), (char **) &o_ptr);
    memcpy((*out) + 16*i, o_ptr, 16);
    icmt_ctr(ctr_block, &ctr_block, 1);
  }
}

void aes_ctr_256(uint8_t * in, int ilen, uint8_t * block, uint8_t * key, uint8_t ** out){
  uint8_t * ctr_block = block;

  uint8_t * pad;
  (*out) = malloc(ilen * sizeof(uint8_t));
  
  for(int i = 0; i < ilen/16; i++){
    uint8_t * i_ptr = in + 16*i;
    uint8_t * o_ptr = malloc(sizeof(uint8_t) * 16);
    aes_256_encrypt(ctr_block, &pad, key);
    xorEncode(i_ptr, pad, 16*sizeof(uint8_t), (char **) &o_ptr);
    memcpy((*out) + 16*i, o_ptr, 16);
    icmt_ctr(ctr_block, &ctr_block, 1);
  }
}
