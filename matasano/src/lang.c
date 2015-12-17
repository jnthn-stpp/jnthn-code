#include "lang.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

double frequencies[27] = {0.0812, 0.0149, 0.0271, 0.0432, 0.1202,
			  0.0230, 0.0203, 0.0592, 0.0731, 0.0010,
			  0.0069, 0.0398, 0.0261, 0.0695, 0.0786,
			  0.0182, 0.0011, 0.0602, 0.0628, 0.0910,
			  0.0228, 0.0111, 0.0209, 0.0017, 0.0211,
			  0.0007, 0.2000};

int * freqAnalysis(char * text, int length){
  int * letters = malloc(sizeof(int) * 27);
  for(int i = 0; i < 27; i++){
    letters[i] = 0;
  }
  for(int i = 0; i < length; i++){
    char letter = text[i];
    if(letter >= 'A' && letter <= 'Z'){
      letter -= 'A';
    } else if(letter >= 'a' && letter <= 'z'){
      letter -= 'a';
    } else if(letter ==  0x20){
      letter = 26;
    }else{
      continue;
    }
    letters[letter]++;
  }
  return letters;
}

int scoreText(char* text, int length){
  int * analysis = freqAnalysis(text, length);
  int score = 0;
  for(int i = 0; i < 26; i++){
    int expected = frequencies[i] * length;
    score += abs(expected - analysis[i]);
  }
  
  score += 10 * abs((frequencies[26] * length) - analysis[26]);
  free(analysis);
  return score;
}
