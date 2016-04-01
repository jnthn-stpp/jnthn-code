#include "sha3.h"
#include "unity_fixture.h"
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "data.h"

uint8_t * start = "a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a30000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
uint8_t * theta_d = "0000000000000000a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3e4e4e4e4e4e4e4e4a3a3a3a3a3a3a3a30000000000000000a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3a3e4e4e4e4e4e4e4e40000000000000000a3a3a3a3a3a3a3a30000000000000000000000000000000047474747474747470000000000000000a3a3a3a3a3a3a3a30000000000000000000000000000000047474747474747470000000000000000a3a3a3a3a3a3a3a30000000000000000000000000000000047474747474747470000000000000000";
uint8_t * rho_d = "00000000000000004747474747474747e8e8e8e8e8e8e8e84e4e4e4e4e4e4e4e1d1d1d1d1d1d1d1d00000000000000003a3a3a3a3a3a3a3ae8e8e8e8e8e8e8e8727272727272727200000000000000001d1d1d1d1d1d1d1d000000000000000000000000000000008e8e8e8e8e8e8e8e0000000000000000474747474747474700000000000000000000000000000000e8e8e8e8e8e8e8e800000000000000008e8e8e8e8e8e8e8e0000000000000000000000000000000047474747474747470000000000000000";
uint8_t * pi_d = "00000000000000003a3a3a3a3a3a3a3a0000000000000000e8e8e8e8e8e8e8e800000000000000004e4e4e4e4e4e4e4e00000000000000001d1d1d1d1d1d1d1d000000000000000000000000000000004747474747474747e8e8e8e8e8e8e8e88e8e8e8e8e8e8e8e00000000000000008e8e8e8e8e8e8e8e1d1d1d1d1d1d1d1d0000000000000000000000000000000000000000000000004747474747474747e8e8e8e8e8e8e8e87272727272727272000000000000000047474747474747470000000000000000";
uint8_t * chi_d = "0000000000000000d2d2d2d2d2d2d2d20000000000000000e8e8e8e8e8e8e8e83a3a3a3a3a3a3a3a535353535353535300000000000000001d1d1d1d1d1d1d1d4e4e4e4e4e4e4e4e00000000000000004141414141414141e8e8e8e8e8e8e8e80000000000000000414141414141414126262626262626261d1d1d1d1d1d1d1d0000000000000000474747474747474718181818181818184747474747474747e8e8e8e8e8e8e8e835353535353535350000000000000000afafafafafafafaf1212121212121212";
uint8_t * iota_d = "0100000000000000d2d2d2d2d2d2d2d20000000000000000e8e8e8e8e8e8e8e83a3a3a3a3a3a3a3a535353535353535300000000000000001d1d1d1d1d1d1d1d4e4e4e4e4e4e4e4e00000000000000004141414141414141e8e8e8e8e8e8e8e80000000000000000414141414141414126262626262626261d1d1d1d1d1d1d1d0000000000000000474747474747474718181818181818184747474747474747e8e8e8e8e8e8e8e835353535353535350000000000000000afafafafafafafaf1212121212121212";

uint64_t ** state;
int size = 400;
int nsize;

TEST_GROUP(sha3_step);

void load(uint8_t * data){
  string_to_state(data, &state);
}
void assert_state(uint64_t *** state, uint8_t * data){
  uint8_t * actual;
  uint8_t * expected;
  state_to_string(*state, &actual);
  rawTohex(data, nsize, &expected, &size);
  rawTohex(actual, nsize, &actual, &size);
  TEST_ASSERT_EQUAL_STRING(expected, actual);
}
TEST_SETUP(sha3_step){}
TEST_TEAR_DOWN(sha3_step){}

TEST(sha3_step, rotl){
  uint64_t num = 0x8000000000000000;
  uint64_t res1 = rotl(num, 1);
  uint64_t res2 = rotl(num, 2);
  TEST_ASSERT_TRUE(0x0000000000000001 == res1);
  TEST_ASSERT_TRUE(0x0000000000000002 == res2);
}
TEST(sha3_step, rotr){
  uint64_t num = 0x0000000000000001;
  uint64_t res1 = rotr(num, 1);
  uint64_t res2 = rotr(num, 2);
  TEST_ASSERT_TRUE(0x8000000000000000 == res1);
  TEST_ASSERT_TRUE(0x4000000000000000 == res2);
}

TEST(sha3_step, theta){
  uint8_t * pre;
  uint8_t * post;
  hexToraw(start, size, &pre, &nsize);
  hexToraw(theta_d, size, &post, &nsize);
  load(pre);
  theta(&state);
  assert_state(&state, post);
}
TEST(sha3_step, rho){
  uint8_t * pre;
  uint8_t * post;
  hexToraw(theta_d, size, &pre, &nsize);
  hexToraw(rho_d, size, &post, &nsize);
  load(pre);
  rho(&state);
  assert_state(&state, post);
}
TEST(sha3_step, pi){
  uint8_t * pre;
  uint8_t * post;
  hexToraw(rho_d, size, &pre, &nsize);
  hexToraw(pi_d, size, &post, &nsize);
  load(pre);
  pi(&state);
  assert_state(&state, post);
}
TEST(sha3_step, chi){
  uint8_t * pre;
  uint8_t * post;
  hexToraw(pi_d, size, &pre, &nsize);
  hexToraw(chi_d, size, &post, &nsize);
  load(pre);
  chi(&state);
  assert_state(&state, post);
}
TEST(sha3_step, iota){
  uint8_t * pre;
  uint8_t * post;
  hexToraw(chi_d, size, &pre, &nsize);
  hexToraw(iota_d, size, &post, &nsize);
  load(pre);
  iota(&state, 0);
  assert_state(&state, post);
}

TEST_GROUP_RUNNER(sha3_step){
  RUN_TEST_CASE(sha3_step, rotr);
  RUN_TEST_CASE(sha3_step, rotl);
  RUN_TEST_CASE(sha3_step, theta);
  RUN_TEST_CASE(sha3_step, rho);
  RUN_TEST_CASE(sha3_step, pi);
  RUN_TEST_CASE(sha3_step, chi);
  RUN_TEST_CASE(sha3_step, iota);
}
