#include "jcpu.h"
#include <stdlib.h>

void proc_init(int mem_size, processor * cpu){
  cpu->dta = malloc(mem_size * sizeof(WORD));
  cpu->mem_size = mem_size;
  cpu->reg[0] = 0;
}

void proc_dest(processor * cpu){
  free(cpu->dta);
}

int proc_load(WORD * pgm, int pgm_size, processor * cpu){
  if(pgm_size > cpu->mem_size){
    return -1;
  }
  int i;
  for(i = 0; i < pgm_size; i++){
    cpu->dta[i] = pgm[i];
  }
  return 1;
}

char proc_cycle(processor * cpu){
  char running = 1;
  char segfault = 0;
  int offset = 0; // bytes to skip at end
  cpu->reg[REG_IR] = cpu->dta[cpu->reg[REG_PC]]; //ir = dta[pc]
  offset++;
  cpu->reg[REG_AM] = cpu->dta[cpu->reg[REG_PC] + sizeof(char)]; // am = dta[pc + 1]
  offset++;
  
  switch(cpu->reg[REG_IR]){
  case OP_NOP :
    offset--;
    break;
  case OP_MVB :
    cpu->reg[REG_A1] = dta[cpu->reg[REG_PC] + 2 * sizeof(char)];
    cpu->reg[REG_A2] = dta[cpu->reg[REG_PC] + 3 * sizeof(char)];
    offset += 2;
    
    switch(cpu->reg[REG_AM]){
    case AM_AA:
      memcpy(cpu->dta + cpu->reg[REG_A2] * sizeof(char),
	     cpu->dta + cpu->reg[REG_A1] * sizeof(char),
	     sizeof(char));
      break;
    case AM_BA:
      memcpy(cpu->dta + cpu->reg[REG_A2] * sizeof(char),
	     cpu->reg[REG_A1],
	     sizeof(char));
    }
    break;
  case OP_END :
    offset--;
    cpu->flags = 1;
  }
  cpu->reg[REG_PC] += offset * sizeof(char);

  //cpu->flags = 0x00;
  //cpu->flags += segfault;
  //cpu->flags = cpu->flags << 1;
  //cpu->flags += running;
  
  return cpu->flags;
}
