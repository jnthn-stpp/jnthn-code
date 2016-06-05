#include "demo.h"
#include "crypto.h"
#include <string.h>

char * demo_aes_e(char * in, char * key){
  int ilen = 32;
  int klen = 32;
  uint8_t * iraw;
  uint8_t * kraw;
  hexToraw(in, ilen, &iraw, &ilen);
  hexToraw((uint8_t *) key, klen, &kraw, &klen);

  aes_128_encrypt(iraw, &iraw, kraw);

  rawTohex(iraw, ilen, &iraw, &ilen);
  return iraw;
}

char * demo_aes_d(char * in, char * key){
  int ilen = 32;
  int klen = 32;
  uint8_t * iraw;
  uint8_t * kraw;
  hexToraw(in, ilen, &iraw, &ilen);
  hexToraw((uint8_t *) key, klen, &kraw, &klen);

  aes_128_decrypt(iraw, &iraw, kraw);

  rawTohex(iraw, ilen, &iraw, &ilen);
  return iraw;
}

char * demo_sha3_224(char * in, int len){
  uint8_t * out = sha3_224(in, len);
  int temp;
  rawTohex(out, 28, &out, &temp);
  return out;
}
char * demo_sha3_256(char * in, int len){
  uint8_t * out = sha3_256(in, len);
  int temp;
  rawTohex(out, 32, &out, &temp);
  return out;
}
char * demo_sha3_384(char * in, int len){
  uint8_t * out = sha3_384(in, len);
  int temp;
  rawTohex(out, 48, &out, &temp);
  return out;
}
char * demo_sha3_512(char * in, int len){
  uint8_t * out = sha3_512(in, len);
  int temp;
  rawTohex(out, 64, &out, &temp);
  return out;
}
char * demo_counter(char * in, int num){
  uint8_t * out;
  int len = 32;
  uint8_t * iraw;
  uint8_t * oraw;
  hexToraw(in, len, &iraw, &len);
  icmt_ctr(iraw, &oraw, num);
  rawTohex(oraw, len, &out, &len);
  return out;
}
