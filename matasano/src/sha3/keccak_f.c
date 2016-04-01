#include "sha3.h"
#include <stdint.h>


void rnd(uint64_t *** state, int rindex){
  theta(state);
  rho(state);
  pi(state);
  chi(state);
  iota(state, rindex);
}

uint8_t * keccak_f(uint8_t * in){
  uint64_t ** state = 0;
  uint64_t first[24];
  uint8_t * out;
  string_to_state(in, &state);
  for(int i = 0; i < 24; i++){
    rnd(&state, i);
    first[i] = state[0][0];
  }
  state_to_string(state, &out);
  //  dest_state(&state);
  return out;
}
