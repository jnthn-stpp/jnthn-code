#include "aes.h"
#include "matrix.h"
#include "data.h"
#include <stdint.h>
#include <stdio.h>

uint8_t ** state;

int main(){
  uint8_t * plaintext = "00112233445566778899aabbccddeeff";
  uint8_t * key = "000102030405060708090a0b0c0d0e0f";
  uint8_t * out;
  uint8_t * temp;
  int plength = 32;
  int klength = 32;
  hexToraw(plaintext, plength, &plaintext, &plength);
  hexToraw(key, klength, &key, &klength);

  aes_128_encrypt(plaintext, &out, key);
  rawTohex(out, plength, &temp, &klength);
  printf("cyphertext: %s\n", temp);
  aes_128_decrypt(out, &out, key);
  rawTohex(out, plength, &out, &klength);
  printf("deciphered: %s\n", out);
}
