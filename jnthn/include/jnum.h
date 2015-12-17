#ifndef JNUM_H
#define JNUM_H
namespace jnthn{
  namespace num{

    class jnum{
    public:
      int * data;
      int length;
      int radix;
      int fpoint;

      bool sign; //true = positive; false = negative

    public:

      jnum(char * str, int size, int radix = 10);
      jnum(int * dta, int size, int radix);
      
      jnum operator+(const jnum& rhs)const;

    };
  }

}

#endif
