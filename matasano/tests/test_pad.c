#include "pad.h"
#include "unity_fixture.h"
#include <stdint.h>
#include <string.h>

uint8_t * test;
uint8_t * pad;

TEST_GROUP(pad);
TEST_SETUP(pad){};
TEST_TEAR_DOWN(pad){};

void pad_given(uint8_t * b){
  TEST_ASSERT_EQUAL_STRING(b, pad);
}

TEST(pad, arb){
  pad = "hello world";
  pad_arb(&pad, 12, '!');
  pad_given("hello world!");
}

TEST(pad, narb){
  pad = "hello world";
  pad_narb(&pad, 11, 12, '!');
  pad_given("hello world!");
}

TEST_GROUP_RUNNER(pad){
  RUN_TEST_CASE(pad, arb);
  RUN_TEST_CASE(pad, narb);
}
