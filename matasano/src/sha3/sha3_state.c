#include "sha3.h"
#include <stdint.h>
#include <stdlib.h>

void init_state(uint64_t *** state){
  uint64_t ** temp = malloc(5 * sizeof(uint64_t *));
  for(int i = 0; i < 5; i++){
    temp[i] = malloc(5 * sizeof(uint64_t));
  }
  (*state) = temp;
}

void dest_state(uint64_t *** state){
  for(int i = 0; i < 5; i++){
    free((*state)[i]);
  }
  free(*state);
}

void string_to_state(uint8_t * in, uint64_t *** state){
  init_state(state);
  for(int y = 0; y < 5; y++){
    for(int x = 0; x < 5; x++){
      for(int z = 0; z < 8; z++){
	(*state)[x][y] |= ((uint64_t) in[z + 8*x + 40*y] << 8*z);
      }
    }
  }
}

void state_to_string(uint64_t ** state, uint8_t ** out){
  (*out) = malloc(25 * 8 * sizeof(uint8_t));
  for(int y = 0; y < 5; y++){
    for(int x = 0; x < 5; x++){
      for(int z = 0; z < 8; z++){
	(*out)[40*y + 8*x + z] = ((uint8_t)(state[x][y] >> 8*z));
      }
    }
  }
}
