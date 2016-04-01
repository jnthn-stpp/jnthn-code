#include "sha3.h"
#include <stdint.h>
#include <stdlib.h>

int rho_off [25] = {0, 1, 190, 28, 91,
		    36, 300, 6, 55, 276,
		    3, 10, 171, 153, 231,
		    105, 45, 15, 21, 136,
		    210, 66, 253, 120, 78};

uint64_t rotl(uint64_t num, int rot){
  uint64_t ret = (num << rot) | ( num >> (64 - rot));
  return ret;
}

uint64_t rotr(uint64_t num, int rot){
    uint64_t ret = (num >> rot) | ( num << (64 - rot));
    return ret;
}

void theta(uint64_t *** state){
  uint64_t ** temp;
  init_state(&temp);
  uint64_t * c = malloc(5 * sizeof(uint64_t));
  for(int i = 0; i < 5; i++){
    c[i] = (*state)[i][0] ^
      (*state)[i][1] ^ (*state)[i][2] ^
      (*state)[i][3] ^ (*state)[i][4];
  }
  for(int x = 0; x < 5; x++){
    for(int y = 0; y < 5; y++){
      temp[x][y] = (*state)[x][y] ^ c[(x+4)%5] ^ rotl(c[(x+1)%5], 1);
    }
  }
  (*state) = temp;
}

void rho(uint64_t *** state){
  uint64_t ** temp;
  init_state(&temp);
  for(int x = 0; x < 5; x++){
    for(int y = 0; y < 5; y++){
      temp[x][y] = rotl((*state)[x][y], rho_off[5*y + x]);
    }
  }
  (*state) = temp;
}

void pi(uint64_t *** state){
  uint64_t ** temp;
  init_state(&temp);
  for(int x = 0; x < 5; x++){
    for(int y = 0; y < 5; y++){
      temp[x][y] = (*state)[(x+3*y)%5][x];
    }
  }
  (*state) = temp;
}

void chi(uint64_t *** state){
  uint64_t ** temp;
  init_state(&temp);
  for(int x = 0; x < 5; x++){
    for(int y = 0; y < 5; y++){
      temp[x][y] = (*state)[x][y] ^
	((~(*state)[(x+1)%5][y]) & (*state)[(x+2)%5][y]);
      //note, use ~ not ! for bitwise
    }
  }
  (*state) = temp;
}

/*uint8_t rc(int t){
  if(t%255 == 0){
    return 1;
  }
  // data >> 7 = data[8]
  uint16_t data = 1;
  for(int i = 0; i <= t; i++){
    data ^= (data >> 7);
    data ^= ((data << 11) >> 14) << 5;// obvious code needs no comments
    data ^= ((data << 10) >> 14) << 6;
    data ^= ((data << 9) >> 14) << 7;
    data &= 0x00ff;
  }
  return (uint8_t)((data >> 14) << 14);
}*/

uint64_t rc[24] = {
  0x0000000000000001, 0x0000000000008082,
  0x800000000000808a, 0x8000000080008000,
  0x000000000000808b, 0x0000000080000001,
  0x8000000080008081, 0x8000000000008009,
  0x000000000000008a, 0x0000000000000088,
  0x0000000080008009, 0x000000008000000a,
  0x000000008000808b, 0x800000000000008b,
  0x8000000000008089, 0x8000000000008003,
  0x8000000000008002, 0x8000000000000080,
  0x000000000000800a, 0x800000008000000a,
  0x8000000080008081, 0x8000000000008080,
  0x0000000080000001, 0x8000000080008008
};

void iota(uint64_t *** state, int index){
  uint64_t rcon = rc[index];
  /*  for(int j = 0; j < 6; j++){
    int pos = (1 << j) - 1;
    uint64_t b = rc(j + 7*index);
    rcon |= (b << pos);
    }*/
  (*state)[0][0] ^= rcon;
}

