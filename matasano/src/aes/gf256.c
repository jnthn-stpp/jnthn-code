#include "aes.h"
#include <stdint.h>


uint8_t gf256_mult(uint8_t a, uint8_t b){
  if(a == 0 || b == 0){
    return 0x00;
  }
  int temp = 0;
  if(b & (1 << 7)){
    temp ^= a;
  }
  for(int i = 0; i < 7; i++){
    b <<= 1;
    temp <<= 1;
    if(b & (1 << 7)){
      temp ^= a;
    }
  }
  temp = gf256_mod(temp, 0x011b);
  return (uint8_t)temp;
}

uint16_t gf256_mod(uint16_t a, uint16_t b){
  int a_length = 16;
  int b_length = 16;
  for(int i = b_length; i > 0; i--){
    int temp = b & (1 << (i - 1));
    if(temp){
      b_length = i;
      break;
    }
  }
  int dif = 16;
  do{
    for(int i = a_length; i > 0; i--){
      int temp = a & (1<< (i - 1));
      if(temp){
	a_length = i;
	break;
      }
    }
    dif = a_length - b_length;
    a ^= (b << dif);
  } while (dif > 0);    
  return a;
}
