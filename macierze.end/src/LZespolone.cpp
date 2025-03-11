#include "LZespolone.hh"
#include <iostream>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
 LZespolona Sprzezenie(LZespolona Skl1)
 {
     LZespolona Skl2=Skl1;
     Skl2.im=Skl1.im*(-1);
     return Skl2;
 }
 double Modul2(LZespolona Skl1)
 {
     return (Skl1.re)*(Skl1.re)+(Skl1.im)*(Skl1.im);
 }
LZespolona  operator + (LZespolona  Skl1,  LZespolona  Skl2)
{
  LZespolona  Wynik;

  Wynik.re = Skl1.re + Skl2.re;
  Wynik.im = Skl1.im + Skl2.im;
  return Wynik;
}

LZespolona  operator - (LZespolona  Skl1,  LZespolona  Skl2)
{
  LZespolona  Wynik;

  Wynik.re = Skl1.re - Skl2.re;
  Wynik.im = Skl1.im - Skl2.im;
  return Wynik;
}
LZespolona  operator * (LZespolona  Skl1,  LZespolona  Skl2)
{
  LZespolona  Wynik;

  Wynik.re = (Skl1.re * Skl2.re) - (Skl1.im * Skl2.im);
  Wynik.im = (Skl1.im * Skl2.re) + (Skl1.re * Skl2.im);
  return Wynik;
}
LZespolona  operator / (LZespolona  Skl1,  LZespolona  Skl2)
{
  LZespolona  Wynik;
  double modul = Modul2(Skl2);

  if(modul!=0) {
  Wynik = Skl1*Sprzezenie(Skl2);
  Wynik.re = Wynik.re / modul;
  Wynik.im = Wynik.im / modul;
  } else {
    std::cout<<"Drogi uzytkowniku nie dzielimy przez 0!"<<std::endl;
  }
  return Wynik;
}
bool operator == (LZespolona Skl1, LZespolona Skl2)
{
    return (Skl1.im == Skl2.im) && (Skl1.re == Skl2.re);
}
LZespolona &LZespolona::operator=(double arg)
{
    this->re = arg;
    this->im = 0;
    return *this;
}

ostream & operator << (ostream& wyjscie,const LZespolona Skl1)
{
  wyjscie<<"("<<Skl1.re;
  wyjscie << showpos << Skl1.im << noshowpos <<"i)";
  return wyjscie;
}
istream & operator >> (istream & rStrmWe, LZespolona & Skl1)
{
  char znak;
  char supportznak;

  rStrmWe>> skipws >>znak;
  //sprawdzenie czy zaczyna sie (
  if(znak!='(')
  {
    rStrmWe.setstate(ios::failbit);
    return rStrmWe;
  }

  rStrmWe>> skipws >> znak;
  // znak urojonej
  if(znak=='i') {
    //gdy jest samo i
    Skl1.re=0;
    Skl1.im=1;

    rStrmWe>> skipws >> znak;
    if(znak !=')')
    {
      rStrmWe.setstate(ios::failbit);
      return rStrmWe;
    }
    return rStrmWe;
  } else if (znak =='+' || znak=='-')
  { // gdy mamy +i lub -i
    supportznak=znak;
    rStrmWe>> skipws >> znak;
    if(znak=='i')
    {
      Skl1.re=0;
      if(supportznak=='+') Skl1.im=1;
      else Skl1.im=-1;

   rStrmWe>> skipws >> znak;
   if(znak !=')')
   {
      rStrmWe.setstate(ios::failbit);
      return rStrmWe;
   }
   return rStrmWe;
    }
  }
  //nie byl to znak ani 'i'
  rStrmWe.putback(znak);
  rStrmWe>>Skl1.re;
  if(rStrmWe.fail())
  {
    rStrmWe.setstate(ios::failbit);
    return rStrmWe;
  }
  // ujemne re 
  if(supportznak=='-') Skl1.re=(-1)*Skl1.re;

  supportznak='p';
  //sukces wczytania re
  rStrmWe>>skipws>>znak;
  //+C -C C 
  if(znak==')') return rStrmWe;
  else if(znak=='i')
  { //Ci -Ci samo im 
  Skl1.im=Skl1.re;
  Skl1.re=0;

  rStrmWe>>skipws>>znak;
  if(znak!=')')
  {
    rStrmWe.setstate(ios::failbit);
    return rStrmWe;
  }
  return rStrmWe;
  }
  else if(znak=='+' || znak=='-')
  {
    supportznak=znak;
    rStrmWe>>skipws>>znak;

    if(znak=='i')
    {
      if(supportznak='+') Skl1.im=1;
      else Skl1.im=-1;

    rStrmWe>>skipws>>znak;
    if(znak!=')')
    {
      rStrmWe.setstate(ios::failbit);
      return rStrmWe;
    } 
    return rStrmWe;
    }
    rStrmWe.putback(znak);
  } else {
    rStrmWe.setstate(ios::failbit);
    return rStrmWe;
  }

  rStrmWe>>Skl1.im;
  if(rStrmWe.fail())
  {
    rStrmWe.setstate(ios::failbit);
    return rStrmWe;
  }
  if(supportznak=='-') Skl1.im=(-1)*Skl1.im;

  rStrmWe>>skipws>>znak;
  if(znak!='i')
  {
    rStrmWe.setstate(ios::failbit);
    return rStrmWe;
  }

  rStrmWe>>skipws>>znak;
  if(znak!=')')
  {
    rStrmWe.setstate(ios::failbit);
    return rStrmWe;
  }

  return rStrmWe;
}
LZespolona operator+=(LZespolona &arg1, LZespolona arg2)
{
    arg1 = arg1 + arg2;
    return arg1;
}
LZespolona operator-=(LZespolona &arg1, LZespolona arg2)
{
    arg1 = arg1 - arg2;
    return arg1;
}
LZespolona operator*=(LZespolona &arg1, LZespolona arg2)
{
    arg1 = arg1 * arg2;
    return arg1;
}
double abs(LZespolona arg)
{
    return sqrt(arg.re * arg.im);
}
LZespolona operator*=(LZespolona &arg1, int arg2)
{
    arg1.re = arg1.re * arg2;
    arg1.im = arg1.im * arg2;
    return arg1;
}
LZespolona operator/=(LZespolona &arg1, LZespolona arg2)
{
    arg1 = arg1 / arg2;
    return arg1;
}
bool operator<(LZespolona arg1, LZespolona arg2) {
  return (arg1.re < arg2.re && arg1.im < arg2.im);
}
bool operator>(LZespolona arg1, LZespolona arg2) {
  return (arg1.re > arg2.re && arg1.im > arg2.im);
}