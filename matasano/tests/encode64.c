#include "crypto.h"
#include <stdio.h>

int main(){
  char* data = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  int length = 96;
  hexToraw(data, length, &data, &length);
  printf("raw: %s \n", data);
  rawTohex(data, length, &data, &length);
  printf("hex: %s \n", data);
  rawTob64(data, length, &data, &length);
  printf("b64: %s \n", data);
}
