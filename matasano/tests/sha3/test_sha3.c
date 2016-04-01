#include "unity_fixture.h"


static void RunAllTests(void){
  RUN_TEST_GROUP(sha3_state);
  RUN_TEST_GROUP(sha3_step);
  RUN_TEST_GROUP(sha3_main);
}

int main(int argc, const char ** argv){
  return UnityMain(argc, argv, RunAllTests);
}
