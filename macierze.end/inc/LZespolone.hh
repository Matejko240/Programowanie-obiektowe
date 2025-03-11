#ifndef LZESPOLONE_HH
#define LZESPOLONE_HH

#include <iostream>

struct  LZespolona {
  double   re;    /*! Pole repezentuje czesc rzeczywista. */
  double   im;    /*! Pole repezentuje czesc urojona. */
  LZespolona &operator=(double arg);
  friend void swap(LZespolona& a, LZespolona& b)
    {
        using std::swap; // bring in swap for built-in types

        swap(a.im, b.im);
        swap(a.re, b.re);
    }
};


/*
 * Dalej powinny pojawic sie zapowiedzi definicji przeciazen operatorow
 */
LZespolona Sprzezenie(LZespolona);
double Modul2(LZespolona);
LZespolona  operator + (LZespolona  Skl1,  LZespolona  Skl2);
LZespolona  operator - (LZespolona  Skl1,  LZespolona  Skl2);
LZespolona  operator * (LZespolona  Skl1,  LZespolona  Skl2);
LZespolona  operator / (LZespolona  Skl1,  LZespolona  Skl2);
bool operator == (LZespolona Skl1, LZespolona Skl2);
std::ostream& operator << (std::ostream& Strm_Wy,const LZespolona Skl1);
std::istream& operator >> (std::istream& Strm_Wej,LZespolona &Skl1);
bool operator<(LZespolona arg1, LZespolona arg2);
bool operator>(LZespolona arg1, LZespolona arg2);
LZespolona  operator*=(LZespolona  &Skl1,  LZespolona  Skl2);
LZespolona  operator*=(LZespolona  &Skl1,  int  Skl2);
LZespolona  operator/=(LZespolona  &Skl1,  LZespolona  Skl2);
LZespolona  operator-=(LZespolona  &Skl1,  LZespolona  Skl2);
LZespolona  operator+=(LZespolona  &Skl1,  LZespolona  Skl2);
double abs(LZespolona arg);
#endif