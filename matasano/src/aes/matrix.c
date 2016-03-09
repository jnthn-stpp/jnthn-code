#include "aes.h"
#include <stdlib.h>
#include <stdint.h>

void init_matrix(uint8_t *** dest, int row, int col){
  (*dest) = malloc(sizeof(uint8_t *) * row);
  for(int i = 0; i < col; i++){
    (*dest)[i] = malloc(sizeof(uint8_t) * col);
  }
}

int mul_matrix(uint8_t ** lhand, int lr, int lc, uint8_t ** rhand, int rr, int rc, uint8_t *** out){
  if(lc != rr){
    return 0;
  }
  init_matrix(out, lr, rc);
  for(int r = 0; r < lr; r++){
    for(int c = 0; c < rc; c++){
      (*out)[r][c] = 0;
      for(int i = 0; i < lc; i++){
	(*out)[r][c] += (lhand[r][lc] * rhand[lc][c]);
      }
    }
  }
}
