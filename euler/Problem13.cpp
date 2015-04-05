#include "jnum.h"
#include <cstring>
#include <iostream>

using namespace jnthn::num;

int main(int argc, char* argv[]){
  std::cout << argc << std::endl;

  char* result;

  result = strtok(argv[1], "\n");

  while(result != NULL){
    std::cout << result << std::endl;

    result = strtok(NULL, "\n");
  }

}
