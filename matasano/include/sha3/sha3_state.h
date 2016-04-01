#ifndef SHA3_STATE_H
#define SHA3_STATE_H

#include <stdint.h>
void init_state(uint64_t *** state);
void dest_state(uint64_t *** state);
void string_to_state(uint8_t * in, uint64_t *** state);
void state_to_string(uint64_t ** state, uint8_t ** out);
uint8_t * state_i(uint64_t ** state, int x, int y, int z);

#endif
