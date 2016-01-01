#include "aes.h"
#include "matrix.h"
#include "gf256.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t sbox[16][16] = {
  {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
  {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
  {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
  {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
  {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
  {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
  {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
  {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
  {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
  {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
  {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
  {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
  {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
  {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
  {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
  {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

uint8_t isbox[16][16] = {
  {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb}, 
  {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb}, 
  {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e}, 
  {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25}, 
  {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92}, 
  {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84}, 
  {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06}, 
  {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b}, 
  {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73}, 
  {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e}, 
  {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b}, 
  {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4}, 
  {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f}, 
  {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef}, 
  {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61}, 
  {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
};

uint8_t rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

void addRoundKey(uint8_t *** state, uint8_t * rkey){
  uint8_t ** res;
  init_matrix(&res, 4, 4);
  for(int r = 0; r < 4; r++){
    for(int c = 0; c < 4; c++){
      res[r][c] = (*state)[r][c] ^ rkey[(4 * c) + r];
    }
  }
  free(*state);
  (*state) = res;
}
void subBytes(uint8_t *** state){
  uint8_t ** res;
  init_matrix(&res, 4, 4);
  for(int r = 0; r < 4; r++){
    for(int c = 0; c < 4; c++){
      res[r][c] = sbox[(*state)[r][c] / 0x10][(*state)[r][c] % 0x10];
    }
  }
  free(*state);
  (*state) = res;
}

void invSubBytes(uint8_t *** state){
  uint8_t ** res;
  init_matrix(&res, 4, 4);
  for(int r = 0; r < 4; r++){
    for(int c = 0; c < 4; c++){
      res[r][c] = isbox[(*state)[r][c] / 0x10][(*state)[r][c] % 0x10];
    }
  }
  free(*state);
  (*state) = res;
}

void shiftRows(uint8_t *** state){
  uint8_t ** res;
  init_matrix(&res, 4, 4);
  for(int row = 0; row < 4; row++){
    for(int col = 0; col < 4; col++){
      res[row][col] = (*state)[row][(col + row) % 4];
    }
    free((*state)[row]);
  }
  free((*state));
  (*state) = res;
}
void invShiftRows(uint8_t *** state){
  uint8_t ** res;
  init_matrix(&res, 4, 4);
  for(int row = 0; row < 4; row++){
    for(int col = 0; col < 4; col++){
      res[row][col] = (*state)[row][(4 + col - row) % 4];
    }
    free((*state)[row]);
  }
  free((*state));
  (*state) = res;
}

void mixColumns(uint8_t *** state){
  uint8_t ** res;
  init_matrix(&res, 4, 4);
  for(int col = 0; col < 4; col++){
    res[0][col] = gf256_mult((*state)[0][col], 0x02) ^
      gf256_mult((*state)[1][col], 0x03) ^
      (*state)[2][col] ^ (*state)[3][col];
    
    res[1][col] = gf256_mult((*state)[1][col], 0x02) ^
      gf256_mult((*state)[2][col], 0x03) ^
      (*state)[0][col] ^ (*state)[3][col];

    res[2][col] = gf256_mult((*state)[2][col], 0x02) ^
      gf256_mult((*state)[3][col], 0x03) ^
      (*state)[0][col] ^ (*state)[1][col];

    res[3][col] = gf256_mult((*state)[3][col], 0x02) ^
      gf256_mult((*state)[0][col], 0x03) ^
      (*state)[2][col] ^ (*state)[1][col];
    
  }
  free(*state);
  (*state) = res;
}

void invMixColumns(uint8_t *** state){
  uint8_t ** res;
  init_matrix(&res, 4, 4);
  for(int col = 0; col < 4; col++){
    res[0][col] =
      gf256_mult((*state)[0][col], 0x0e) ^
      gf256_mult((*state)[1][col], 0x0b) ^
      gf256_mult((*state)[2][col], 0x0d) ^
      gf256_mult((*state)[3][col], 0x09);
    res[1][col] =
      gf256_mult((*state)[0][col], 0x09) ^
      gf256_mult((*state)[1][col], 0x0e) ^
      gf256_mult((*state)[2][col], 0x0b) ^
      gf256_mult((*state)[3][col], 0x0d);
    res[2][col] =
      gf256_mult((*state)[0][col], 0x0d) ^
      gf256_mult((*state)[1][col], 0x09) ^
      gf256_mult((*state)[2][col], 0x0e) ^
      gf256_mult((*state)[3][col], 0x0b);
    res[3][col] =
      gf256_mult((*state)[0][col], 0x0b) ^
      gf256_mult((*state)[1][col], 0x0d) ^
      gf256_mult((*state)[2][col], 0x09) ^
      gf256_mult((*state)[3][col], 0x0e);
        
  }
  free(*state);
  (*state) = res;
}

void subWord(uint8_t ** temp){
  for(int i = 0; i < 4; i++){
    (*temp)[i] = sbox[(*temp)[i] / 0x10][(*temp)[i] % 0x10];
  }
}

void rotWord(uint8_t ** temp){
  uint8_t * res = malloc(4 * sizeof(uint8_t));
  for(int i = 0; i < 4; i++){
    res[i] = (*temp)[(i + 1) % 4];
  }
  free(*temp);
  (*temp) = res;
}

void keySchedule(uint8_t * key, uint8_t ** out, int keylen, int rounds){
  (*out) = malloc((rounds + 1) * 16 * sizeof(uint8_t));

  uint8_t * temp = malloc(4);
  int i = 0;
  while(i < keylen){
    (*out)[4*i] = key[4*i];
    (*out)[4*i + 1] = key[4*i + 1];
    (*out)[4*i + 2] = key[4*i + 2];
    (*out)[4*i + 3] = key[4*i + 3];
    i++;
  }
  i = keylen;
  while(i < 4 * (rounds + 1)){
    temp[0] = (*out)[4*(i - 1)];
    temp[1] = (*out)[4*(i - 1) + 1];
    temp[2] = (*out)[4*(i - 1) + 2];
    temp[3] = (*out)[4*(i - 1) + 3];

    if(i % keylen == 0){
      rotWord(&temp);
      subWord(&temp);
      temp[0] ^= rcon[(i / keylen) - 1];
    } else if((keylen > 6) && (i % keylen) == 4){
      subWord(&temp);
    }

    (*out)[4*i] = (*out)[4*(i - keylen)] ^ temp[0];
    (*out)[4*i + 1] = (*out)[4*(i - keylen) + 1] ^ temp[1];
    (*out)[4*i + 2] = (*out)[4*(i - keylen) + 2] ^ temp[2];
    (*out)[4*i + 3] = (*out)[4*(i - keylen) + 3] ^ temp[3];
    i++;
  }
}

void aesEncrypt(uint8_t * in, uint8_t ** out, uint8_t * key, int rounds){
  uint8_t ** state;
  init_matrix(&state, 4, 4);
  (*out) = malloc(sizeof(uint8_t) * 16);

  for(int r = 0; r < 4; r++){
    for(int c = 0; c < 4; c++){
      state[r][c] = in[4*c + r];
    }
  }

  addRoundKey(&state, key);
  for(int i = 1; i < rounds; i++){
    subBytes(&state);
    shiftRows(&state);
    mixColumns(&state);
    addRoundKey(&state, key + i*16); //here be segfaults
  }

  subBytes(&state);
  shiftRows(&state);
  addRoundKey(&state, key + rounds * 16);

  for(int r = 0; r < 4; r++){
    for(int c = 0; c < 4; c++){
      (*out)[4*c + r] = state[r][c];
    }
  }

  
}

void aes_128_encrypt(uint8_t * in, uint8_t ** out, uint8_t * key){
  uint8_t * key_schedule;
  keySchedule(key, &key_schedule, 4, 10);
  aesEncrypt(in, out, key_schedule, 10);
}

void aes_192_encrypt(uint8_t * in, uint8_t ** out, uint8_t * key){
  uint8_t * key_schedule;
  keySchedule(key, &key_schedule, 6, 12);
  aesEncrypt(in, out, key_schedule, 12);
}

void aes_256_encrypt(uint8_t * in, uint8_t ** out, uint8_t * key){
  uint8_t * key_schedule;
  keySchedule(key, &key_schedule, 8, 14);
  aesEncrypt(in, out, key_schedule, 14);
}

void aesDecrypt(uint8_t * in, uint8_t ** out, uint8_t * key, int rounds){
  uint8_t ** state;
  init_matrix(&state, 4, 4);
  (*out) = malloc(sizeof(uint8_t) * 16);

  for(int r = 0; r < 4; r++){
    for(int c = 0; c < 4; c++){
      state[r][c] = in[4*c + r];
    }
  }

  addRoundKey(&state, key + rounds * 16);
  for(int i = rounds - 1; i > 0; i--){
    invShiftRows(&state);
    invSubBytes(&state);
    addRoundKey(&state, key + i*16); //here be segfaults
    invMixColumns(&state);
  }
  
  invShiftRows(&state);
  invSubBytes(&state);
  addRoundKey(&state, key);

  for(int r = 0; r < 4; r++){
    for(int c = 0; c < 4; c++){
      (*out)[4*c + r] = state[r][c];
    }
  }
}

void aes_128_decrypt(uint8_t * in, uint8_t ** out, uint8_t * key){
  uint8_t * key_schedule;
  keySchedule(key, &key_schedule, 4, 10);
  aesDecrypt(in, out, key_schedule, 10);
}

void aes_192_decrypt(uint8_t * in, uint8_t ** out, uint8_t * key){
  uint8_t * key_schedule;
  keySchedule(key, &key_schedule, 6, 12);
  aesDecrypt(in, out, key_schedule, 12);
}

void aes_256_decrypt(uint8_t * in, uint8_t ** out, uint8_t * key){
  uint8_t * key_schedule;
  keySchedule(key, &key_schedule, 8, 14);
  aesDecrypt(in, out, key_schedule, 14);
}
