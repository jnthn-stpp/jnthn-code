#include <stdio.h>
#include <stdlib.h>
#include "jstack.h"

int main(int argc, char * argv[]){

  //find file dimensions
  FILE* ifile = fopen(argv[1], "r");
  
  int rows = 1;
  int cols = 0;
  
  char cur = fgetc(ifile);
  while(cur != '\n' && cur != EOF){  //get number of columns
    cur = fgetc(ifile);
    cols++;
  }
  if(cur == '\n'){
    rows++;
  }
  int count = 0;
  while(cur != EOF){
    cur = fgetc(ifile);
    count++;
    if(cur == '\n'){
      if(count - 1 == cols){
	count = 0;
	rows++;
      } else {
	printf("Dimension error\n");
	printf("Row %d is not %d chars long\n", rows + 1, cols);
	return 2;
      }
    }
  }

  fclose(ifile);

  printf("cols: %d\n", cols);
  printf("rows: %d\n", rows);
  //init pgm array
  char** pgm = malloc(cols * sizeof(char*));
  int i;
  for(i = 0; i < cols; i++){
    pgm[i] = malloc(rows * sizeof(char));
  }

  ifile = fopen(argv[1], "r");
  for(i = 0; i < rows; i++){
    int j;
    for(j = 0; j < cols; j++){
      pgm[i][j] = fgetc(ifile);
      fputc(pgm[i][j], stdout);
    }
    fgetc(ifile);
  }
  fputc('\n', stdout);

  //set up ip (instruction pointer) and begin execution

  char ip = pgm[0][0];
  int crow = 0; //current row
  int ccol = 0; //current col
  int srow = 0; //row direction
  int scol = 1; //col direction

  jstack* stack = malloc(sizeof(jstack));
  initStack(stack, 128);

  int true = 1;
  int false = 0;

  int running = true;
  int strmode = false;
  
  int stackFault = false;
  int syntaxError = false;
  int mathError = false;

  while(running){
    crow %= rows;
    ccol %= cols;
    ip = pgm[crow][ccol];
    if(!strmode){
      switch(ip){
      case '>':
	srow = 0;
	scol = 1;
	break;
      case '<':
	srow = 0;
	scol = -1;
	break;
      case '^':
	srow = -1;
	scol = 0;
	break;
      case 'v':
	srow = 1;
	scol = 0;
	break;
      case '#':
	crow += srow;
	ccol += scol;
	break;
      case '+':
	if(stack->point > 1){
	  int a = pop(stack);
	  int b = pop(stack);
	  a += b;
	  push(stack, a);
	} else {
	  stackFault = true;
	}
	break;
      case '-':
	if(stack->point > 1){
	  int a = pop(stack);
	  int b = pop(stack);
	  b -= a;
	  push(stack, a);
	} else {
	  stackFault = true;
	}
	break;
      case '*':
	if(stack->point > 1){
	  int a = pop(stack);
	  int b = pop(stack);
	  a *= b;
	  push(stack, a);
	} else {
	  stackFault = true;
	}
	break;
      case '/':
	if(stack->point > 1){
	  int a = pop(stack);
	  int b = pop(stack);
	  if(a != 0){
	    b /= a;
	  } else {
	    mathError = true;
	    break;
	  }
	  push(stack, a);
	} else {
	  stackFault = true;
	}
	break;
      case '%':
	if(stack->point > 1){
	  int a = pop(stack);
	  int b = pop(stack);
	  b %= a;
	  push(stack, a);
	} else {
	  stackFault = true;
	}
	break;
      case '@':
	running = false;
	break;
      case '\'':
	if(stack->point > 1){
	  int a = pop(stack);
	  int b = pop(stack);
	  if(b > a){
	    push(stack, 1);
	  } else {
	    push(stack, 0);
	  }
	} else {
	  stackFault = true;
	}
	break;
      case '_':
	if(stack->point > 0){
	  int a = pop(stack);
	  if(a){
	    srow = 0;
	    scol = -1;
	  }else{
	    srow = 0;
	    scol = 1;
	  }
	} else {
	  stackFault = true;
	}
	break;
      case '|':
	if(stack->point > 0){
	  int a = pop(stack);
	  if(a){
	    srow = 1;
	    scol = 0;
	  } else {
	    srow = -1;
	    scol = 0;
	  }
	}else{
	  stackFault = true;
	}
	break;
      case '\"':
	strmode = !strmode;
	break;
      case ':':
	if(stack->point > 0){
	  int a = pop(stack);
	  push(stack, a);
	  push(stack, a);
	}else{
	  stackFault = true;
	}
	break;
      case '\\':
	if(stack->point > 1){
	  int a = pop(stack);
	  int b = pop(stack);
	  push(stack, a);
	  push(stack, b);
	} else {
	  stackFault = true;
	}
	break;
      case '$':
	if(stack->point > 0){
	  pop(stack);
	}else{
	  stackFault = true;
	}
	break;
      case '.':
	if(stack->point > 0){
	  printf("%d", pop(stack));
	} else {
	  stackFault = true;
	}
	break;
       case ',':
	if(stack->point > 0){
	  printf("%c", pop(stack));
	} else {
	  stackFault = true;
	}
	break;
      case '&':
	if(1){
	  int a = 0;
	  scanf("%d", &a);
	  push(stack, a);
	}
	break;
      case '~':
	if(1){
	  int a = 0;
	  scanf("%c", &a);
	  push(stack, a);
	}
	break;
      case ' ':
	break;
      default:
	if('0' <= ip && '9' >= ip){
	  ip -= '0';
	  push(stack, ip);
	} else {
	  syntaxError = true;
	}
	break;
      }
    } else {
      if(ip == '\"'){
	strmode = !strmode;
      } else {
	push(stack, ip);
      }
    }
    crow+=srow;
    ccol+=scol;
  }
} 
 
