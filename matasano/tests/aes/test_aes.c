#include "aes.h"
#include "data.h"
#include "unity_fixture.h"
#include <stdint.h>

uint8_t * pt;
uint8_t * out;
uint8_t * key;
int length;
TEST_GROUP(aes);

TEST_SETUP(aes){
    
}
TEST_TEAR_DOWN(aes){
  
}
void setTextKey(uint8_t * plain, uint8_t * tkey, int klen){
  hexToraw(tkey, klen, &key, &length);
  hexToraw(plain, 32, &pt, &length);
}

void assumeOut(uint8_t * assume){
  rawTohex(out, 16, &out, &length);
  TEST_ASSERT_EQUAL_STRING( assume, out);
}


TEST(aes, encrypt_128){
  setTextKey("00112233445566778899aabbccddeeff", "000102030405060708090a0b0c0d0e0f", 32);
  aes_128_encrypt(pt, &out, key);
  assumeOut("69c4e0d86a7b0430d8cdb78070b4c55a");
}

TEST(aes, decrypt_128){
  setTextKey("69c4e0d86a7b0430d8cdb78070b4c55a", "000102030405060708090a0b0c0d0e0f", 32);

  aes_128_decrypt(pt, &out, key);
  assumeOut("00112233445566778899aabbccddeeff");
}

TEST(aes, encrypt_192){
  setTextKey("00112233445566778899aabbccddeeff", "000102030405060708090a0b0c0d0e0f1011121314151617", 48);
  aes_192_encrypt(pt, &out, key);
  assumeOut("dda97ca4864cdfe06eaf70a0ec0d7191");
}

TEST(aes, decrypt_192){
  setTextKey("dda97ca4864cdfe06eaf70a0ec0d7191", "000102030405060708090a0b0c0d0e0f1011121314151617", 48);
  aes_192_decrypt(pt, &out, key);
  assumeOut("00112233445566778899aabbccddeeff");
}

TEST(aes, encrypt_256){
  setTextKey("00112233445566778899aabbccddeeff", "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f", 64);
  aes_256_encrypt(pt, &out, key);
  assumeOut("8ea2b7ca516745bfeafc49904b496089");
}

TEST(aes, decrypt_256){
  setTextKey("8ea2b7ca516745bfeafc49904b496089", "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f", 64);
  aes_256_decrypt(pt, &out, key);
  assumeOut("00112233445566778899aabbccddeeff");
}

TEST_GROUP_RUNNER(aes){
  RUN_TEST_CASE(aes, encrypt_128);
  RUN_TEST_CASE(aes, decrypt_128);
  RUN_TEST_CASE(aes, encrypt_192);
  RUN_TEST_CASE(aes, decrypt_192);
  RUN_TEST_CASE(aes, encrypt_256);
  RUN_TEST_CASE(aes, decrypt_256);
}
