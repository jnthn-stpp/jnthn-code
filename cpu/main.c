#include "jcpu.h"
#include <stdio.h>

processor * cpu;
int main(int argc, char** argv){
  if(argc != 2){
    exit(-1);
  }
  FILE * file = fopen(argv[1], "r");
  char* pgm = malloc(256 * sizeof(char));

  int i = 0;
  while(!feof(file)){
    fscanf("%c", pgm[i]);
  }

  proc_init(256, cpu);
  proc_load(pgm, 256, cpu);

  while(!(proc_cycle(cpu))){
    proc_print(cpu);
  }
  
}
