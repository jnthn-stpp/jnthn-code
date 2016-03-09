#include "unity_fixture.h"


static void RunAllTests(void){
  RUN_TEST_GROUP(aes);
  RUN_TEST_GROUP(aes_ctr);
  RUN_TEST_GROUP(gf256);
  //RUN_TEST_GROUP(pad);
}

int main(int argc, const char ** argv){
  return UnityMain(argc, argv, RunAllTests);
}

