#ifndef JCPU_H
#define JCPU_H

typedef char WORD;
typedef struct {

  WORD * dta;
  int mem_size;
  long reg[32];
  char flags;
} processor;

void proc_init(int mem_size, processor * cpu);
void proc_dest(processor * cpu);
int proc_load(WORD * pgm, int pgm_size, processor * cpu);
char proc_cycle(processor * cpu);
void proc_print(processor * cpu);
typedef enum REGISTER {
  REG_PC = 0, // program counter
  REG_IR, // instruction register
  REG_AM, // address mode
  REG_A1, // argument 1
  REG_A2, // argument 2
  REG_A3, // argument 3
};

typedef enum OPCODE {
  OP_NOP = 0x00, // no operation
  OP_MVB, // move byte
  OP_MVI, // move int
  OP_MVL, // move long

  OP_END = 0xFF,

};

// key a = address b = absolute r = register
typedef enum ADDRMODE {
  AM_AA = 0x00, //address, address
  AM_BA, // absolute, address
};

#endif
