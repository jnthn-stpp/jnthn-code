#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


uint8_t* key64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void hexToraw(uint8_t* data, int length, uint8_t** out, int* nsize){
  *nsize = length / 2;
  *out = (uint8_t *)malloc(*nsize * sizeof(uint8_t));
  for(int i = 0; i < *nsize; i++){
    uint8_t u16 = data[2*i];
    uint8_t u1 = data[2*i + 1];
    if(u16 >= 'A' && u16 <= 'F'){
      u16 -= 'A';
      u16 += 10;
    } else if(u16 >= 'a' && u16 <= 'z'){
      u16 -= 'a';
      u16 += 10;
    }else {
      u16 -= '0';
    }

    if(u1 >= 'A' && u1 <= 'F'){
      u1 -= 'A';
      u1 += 10;
    } else if(u1 >= 'a' && u1 <= 'z'){
      u1 -= 'a';
      u1 += 10;
    }else {
      u1 -= '0';
    }

    (*out)[i] = (u16 * 0x10) + (u1);
  }
}

void rawTohex(uint8_t* data, int length, uint8_t** out, int * nsize){

  *nsize = length * 2;
  *out = malloc(sizeof(uint8_t) * *nsize);
  
  for(int i = 0; i < length; i++){
    uint8_t u1 = data[i] % 0x10;
    uint8_t u16 = data[i] / 0x10;
    
    if(u1 >= 0x0a && u1 <= 0x0f){
      u1 += 'W'; //dont ask
    } else {
      u1 += '0';
    }

    if((u16 >= 0x0a) && (u16 <= 0x0f)){
      u16 += 'W'; //dont ask
    } else {
      u16 += '0';
    }

    (*out)[2 * i] = u16;
    (*out)[2 * i + 1] = u1;

    //printf("%c, %c ", u16, u1);
  }
}

void rawTob64(uint8_t* data, int length, uint8_t** out, int * nsize){
  *nsize = (length / 3) * 4;
  *out = malloc(sizeof(uint8_t) * (*nsize + (length % 3)));

  int i = 0;
  int extra = 0;
  while(i < length / 3){
    int u256;
    int u16;
    int u1;
    u256 = data[3*i];
    if(3*i + 1 > length){
      extra += 1;
      u16 = 0;
    } else {
      u16 = data[3*i + 1];
    }
    if(3*i + 2 > length){
      extra += 1;
      u1 = 0;
    } else {
      u1 = data[3*i + 2];
    }

    int temp = (0x10000 *  u256) + (0x100 * u16) + u1;
    for(int j = 3; j >= 0; j--){
      int dta = temp % 64;
      (*out)[4*i + j] = key64[dta];
      temp /= 64;
    }
    /* printf("%c, %c, %c, %c, ", 
	   (*out)[4*i + 0], 
	   (*out)[4*i + 1], 
	   (*out)[4*i + 2],
	   (*out)[4*i + 3]); */
    i++;
  }
  for(int i = extra; i > 0; i--){
    (*out)[*nsize + (length % 3) - i] = '=';
  }
}
