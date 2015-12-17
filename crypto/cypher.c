#include <stdio.h>
#include <stdlib.h>
#include "jcode.h"

char* key;

FILE* keyFile;

int main(int argc, char *argv[]){
  key = malloc(26 * sizeof(char));

  keyFile = fopen(argv[1], "r");
  fgets(key, 27, keyFile);

  if(argv[2][0] == 'e'){
    key = encodeKey(key);
  } else if(argv[2][0] == 'd'){
    key = decodeKey(key);
  } else {
    printf("\"%c\" is not a valid option\n", argv[2][0]);
    return 1;
  }
  
  char c;
  do{
    c = fgetc(stdin);
    
    c = code(key, c);
    fputc(c, stdout);
  } while(c != EOF);
  //printf(key);
  free(key);
}
