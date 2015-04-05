#include "../include/jnum.h"
#include <cstdlib>

using namespace jnthn::num;

jnthn::num::jnum::jnum(int * dta, int size, int radix){
  data = dta;
  this->radix = radix;
  this->length = size;
}

jnthn::num::jnum::jnum(char * str, int size, int radix){
  this->length = size;
  this->radix = radix;

  this->data = new int[size];
  for(int i = 1; i <= size; i++){
    
    data[i] = std::atoi(&str[i]);

  }

}
jnum jnthn::num::jnum::operator+(const jnum& rhs) const {
  
  int * rdata = rhs.data;
  int rlength = rhs.length;

  if(rhs.radix != radix){
    throw "Lazy Developer Exception: feature not yet implemented";
  }

  int i = 0;
  int carry = 0;

  int nsize = (length > rlength)? length : rlength;

  int * ndata = new int[nsize];

  while(rlength > i || length > i){

    int r = 0;
    int l = 0;
    
    if(length - i > 0){
      l = data[length - i];
    }

    if(rlength - i > 0){
      r = rdata[rlength - i];
    }

    ndata[nsize - i] = r + l + carry;

    if(ndata[nsize - i] >= radix){
      carry = ndata[nsize - i] / radix;
      ndata[nsize - i] %= radix;
    }

    i++;
  }

  return jnum(ndata, nsize, radix);

}
