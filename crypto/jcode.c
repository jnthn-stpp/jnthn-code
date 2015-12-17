#include <stdlib.h>
#include "jcode.h"

char* encodeKey(char* key){
  char* ret;
  ret = malloc(sizeof(*ret) * 26);
  int i;
  for(i = 0; i < 26; i++){
    ret[i] = key[i];
  }
  return ret;
}

char* decodeKey(char* key){
  char* ret;
  ret = malloc(sizeof(*ret) * 26);
  int i;
  for(i = 0; i < 26; i++){
    ret[i] = '-';
  }
  for(i = 0; i < 26; i++){
    int idx = key[i] - 'a';
    if(idx >= 0 && idx <= 26){
      ret[idx] = i + 'a';
    }
  }
  return ret;
}

char code(char* key, char msg){
  char ret;
  int i;
  if(msg >= 'a' && msg <= 'z'){
    ret = key[msg -'a'];
    if(ret == '-'){
          ret = 'A' + (msg - 'a');
    }
  }else{
    ret = msg;
  }

  return ret;
}
