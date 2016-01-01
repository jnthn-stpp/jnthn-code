#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

void init_matrix(uint8_t *** dest, int row, int col);
void mulxor_matrix(uint8_t ** lhand, int lr, int lc, uint8_t ** rhand, int rr, int rc, uint8_t *** out);

#endif
