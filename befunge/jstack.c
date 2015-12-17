#include <stdlib.h>
#include <string.h>
#include "jstack.h"

void initStack(jstack *stack, int size){
  stack->point = 0;
  stack->length = size;
  stack->dta = malloc(size * sizeof(int));
  int i;
  for(i = 0; i < size; i++){
    stack->dta[i] = 0;
  }
}

int pop(jstack *stack){
  int ret;
  if(stack->point != 0){
    stack->point--;
    ret = stack->dta[stack->point];
  } else {
    ret = 0;
  }
  return ret;
}

void push(jstack *stack, int data){
  if(!(stack->point < stack->length)){
    resize(stack);
  }
  int idx = stack->point;
  stack->dta[idx] = data;
  stack->point++; 
}

void resize(jstack *stack){
  int * n = malloc(sizeof(int)* 2 * stack->length);
  int i;
  stack->length *= 2;
  for(i = 0; i < stack->length; i++){
    n[i] = 0;
  }
  memcpy(n, stack->dta, sizeof(*(stack->dta) * stack->length));
  stack->dta = n;
}

