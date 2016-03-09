#include "aes.h"
#include "unity_fixture.h"
#include <stdint.h>

TEST_GROUP(gf256);
TEST_SETUP(gf256){}
TEST_TEAR_DOWN(gf256){}

TEST(gf256, mult){
  uint8_t res = gf256_mult(0x57, 0x83);
  TEST_ASSERT_EQUAL_UINT8(0xc1, res);
}

TEST(gf256, mod){
  uint16_t res = gf256_mod(0x3f7e, 0x11b);
  TEST_ASSERT_EQUAL_UINT16(0x01, res);
}

TEST_GROUP_RUNNER(gf256){
  RUN_TEST_CASE(gf256, mult);
  RUN_TEST_CASE(gf256, mod);
}
