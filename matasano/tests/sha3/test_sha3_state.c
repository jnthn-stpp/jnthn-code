#include "sha3.h"
#include "unity_fixture.h"
#include <stdint.h>

TEST_GROUP(sha3_state);

TEST_SETUP(sha3_state){}
TEST_TEAR_DOWN(sha3_state){}

TEST(sha3_state, string_state){
  uint8_t * txt = "01234567012345670123456701234567012345670123456701234567012345670123456701234567012345670123456701234567012345670123456701234567012345670123456701234567012345670123456701234567012345670123456701234567";
  uint8_t * out;

  uint64_t ** state;
  string_to_state(txt, &state);
  state_to_string(state, &out);

  TEST_ASSERT_EQUAL_STRING(txt, out);
}

TEST_GROUP_RUNNER(sha3_state){
  RUN_TEST_CASE(sha3_state, string_state);
}
