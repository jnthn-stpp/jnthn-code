#ifndef SHA3_STEP_H
#define SHA3_STEP_H

uint64_t rotl(uint64_t num, int rot);
uint64_t rotr(uint64_t num, int rot);
void theta(uint64_t *** state);
void rho(uint64_t *** state);
void pi(uint64_t *** state);
void chi(uint64_t *** state);
void iota(uint64_t *** state, int index);

#endif
