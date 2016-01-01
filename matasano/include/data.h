#ifndef DATA_H
#define DATA_H
#include <stdint.h>

void rawTob64(uint8_t * data, int length, uint8_t** out, int *o_length);
void hexToraw(uint8_t * data, int length, uint8_t** out, int *o_length);
void b64Toraw(uint8_t * data, int length, uint8_t** out, int *o_length);
void rawTohex(uint8_t * data, int length, uint8_t** out, int *o_length);


#endif
