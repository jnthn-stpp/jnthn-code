#ifndef JSTACK_H
#define JSTACK_H

typedef struct jstack{
  int length;
  int point;
  int * dta;
}jstack;

void initStack(jstack *stack, int size);

int pop(jstack *stack);
void push(jstack *stack, int data);
void resize(jstack *stack);
#endif
