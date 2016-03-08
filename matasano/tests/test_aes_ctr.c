#include "crypto.h"
#include "unity_fixture.h"
#include <stdint.h>
#include <string.h>

TEST_GROUP(aes_ctr);
TEST_SETUP(aes_ctr){}
TEST_TEAR_DOWN(aes_ctr){}

TEST(aes_ctr, icmt){
  //todo write test logic
  uint8_t * test = "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  int len = strlen(test);
  hexToraw(test, len, &test, &len); 
  icmt_ctr(test, &test, 1);
  rawTohex(test, len, &test, &len); 
  TEST_ASSERT_EQUAL_STRING("f0f1f2f3f4f5f6f7f8f9fafbfcfdff00", test);
  hexToraw(test, len, &test, &len); 
  icmt_ctr(test, &test, 1);
  rawTohex(test, len, &test, &len); 
  TEST_ASSERT_EQUAL_STRING("f0f1f2f3f4f5f6f7f8f9fafbfcfdff01", test);
  hexToraw(test, len, &test, &len); 
  icmt_ctr(test, &test, 1);
  rawTohex(test, len, &test, &len); 
  TEST_ASSERT_EQUAL_STRING("f0f1f2f3f4f5f6f7f8f9fafbfcfdff02", test);
}

TEST(aes_ctr, ctr_128){
  uint8_t * test = "6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e51";
  uint8_t * block = "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  uint8_t * key = "2b7e151628aed2a6abf7158809cf4f3c";
  int len = strlen(test);
  int blen = strlen(block);
  int klen = strlen(key);
  hexToraw(test, len, &test, &len);
  hexToraw(block, blen, &block, &blen);
  hexToraw(key, klen, &key, &klen);

  aes_ctr_128(test, len, block, key, &test);
  
  rawTohex(test, len, &test, &len);
  TEST_ASSERT_EQUAL_STRING("874d6191b620e3261bef6864990db6ce9806f66b7970fdff8617187bb9fffdff", test);
}

TEST(aes_ctr, ctr_192){
  uint8_t * test = "6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e51";
  uint8_t * block = "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  uint8_t * key = "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b";
  int len = strlen(test);
  int blen = strlen(block);
  int klen = strlen(key);
  hexToraw(test, len, &test, &len);
  hexToraw(block, blen, &block, &blen);
  hexToraw(key, klen, &key, &klen);

  aes_ctr_192(test, len, block, key, &test);
  
  rawTohex(test, len, &test, &len);
  TEST_ASSERT_EQUAL_STRING("1abc932417521ca24f2b0459fe7e6e0b090339ec0aa6faefd5ccc2c6f4ce8e94", test);
}

TEST(aes_ctr, ctr_256){
  uint8_t * test = "6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e51";
  uint8_t * block = "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  uint8_t * key = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
  int len = strlen(test);
  int blen = strlen(block);
  int klen = strlen(key);
  hexToraw(test, len, &test, &len);
  hexToraw(block, blen, &block, &blen);
  hexToraw(key, klen, &key, &klen);

  aes_ctr_256(test, len, block, key, &test);
  
  rawTohex(test, len, &test, &len);
  TEST_ASSERT_EQUAL_STRING("601ec313775789a5b7a7f504bbf3d228f443e3ca4d62b59aca84e990cacaf5c5", test);
}

TEST_GROUP_RUNNER(aes_ctr){
  RUN_TEST_CASE(aes_ctr, icmt);
  RUN_TEST_CASE(aes_ctr, ctr_128);
  RUN_TEST_CASE(aes_ctr, ctr_192);
  RUN_TEST_CASE(aes_ctr, ctr_256);
}

