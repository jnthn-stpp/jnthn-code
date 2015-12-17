#include <stdio.h>

int main(){
  int count[26] = {0};
  int num = 0;
  char c;
  do{
    c = fgetc(stdin);
    if(c == EOF){
      break;
    }
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
      count[c]++;
      num++;
    }
  }while(c != EOF);
  int i;
  for(i = 0; i < 26; i++){
    printf("%d, ", count[i]);
  }
  printf("%d", num);
}
