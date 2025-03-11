#ifndef WEKTOR_HH
#define WEKTOR_HH

#include "rozmiar.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include "LZespolone.hh"
#include "Wektor.hh"
/*
 *  Tutaj trzeba opisac klase. Jakie pojecie modeluje ta klasa
 *  i jakie ma glowne cechy.
 */
template <typename STyp, int SWymiar> 
class Wektor {
  STyp _Kordy[SWymiar]; //wspolrzedne
  STyp dlugosc;
  public:
  Wektor() { for (STyp &K: _Kordy) K=0; }
    //Przeciazenie poslugiwania sie 
    const STyp &operator[](int index) const;
    STyp &operator[](int index);
    //operatory arytm
    Wektor<STyp, SWymiar> operator+(const Wektor<STyp, SWymiar>  &w) const;
    Wektor<STyp, SWymiar> operator-(const Wektor<STyp, SWymiar>  &w) const;
    float operator*(Wektor<STyp, SWymiar>  w);
    void operator*(STyp arg);
    void operator/(STyp arg);  
};


//template <typename STyp> 
//std::istream& operator >> (std::istream &Strm, Wektor<STyp> &wektor);

//template <typename STyp> 
//std::ostream& operator << (std::ostream &Strm, const Wektor<STyp> &wektor);

template <typename STyp, int SWymiar> 
float oblicz_dlugosc(Wektor<STyp, SWymiar> wektor);

template <typename STyp, int SWymiar> 
const STyp &Wektor<STyp, SWymiar>::operator[](int index) const {
    assert(index >= 0 && index < SWymiar);
    return _Kordy[index];
}

template <typename STyp, int SWymiar>
STyp &Wektor<STyp, SWymiar>::operator[](int index) {
    assert(index >= 0 && index < SWymiar);
    return _Kordy[index];
}

template <typename STyp, int SWymiar>
Wektor<STyp, SWymiar> Wektor<STyp, SWymiar>::operator+(const Wektor<STyp, SWymiar> &w) const {
    Wektor<STyp, SWymiar> wynik;
    for (int i=0; i < SWymiar; i++) {
        wynik[i] = this->_Kordy[i] + w[i];
    }
    return wynik;
}

template <typename STyp, int SWymiar>
float Wektor<STyp, SWymiar>::operator*(Wektor<STyp, SWymiar> w) {
    float sum=0;
    for (int i=0; i < ROZMIAR; i++) {
        sum += this->_Kordy[i] * w[i];
    }
    return sum;
}

template <typename STyp, int SWymiar>
Wektor<STyp, SWymiar> Wektor<STyp, SWymiar>::operator-(const Wektor<STyp, SWymiar> &w) const {
    Wektor wynik;
    for (int i=0; i < SWymiar; i++) {
        wynik[i] = this->_Kordy[i] - w[i];
    }
    return wynik;
}

template <typename STyp, int SWymiar>
void Wektor<STyp, SWymiar>::operator*(STyp arg) {
    for (int i = 0; i < SWymiar; i++)
        this->_Kordy[i] *= arg;
}

template <typename STyp, int SWymiar>
void Wektor<STyp, SWymiar>::operator/(STyp arg) {
    for (int i = 0; i < SWymiar; i++)
        this->_Kordy[i] /= arg;
}

template <typename STyp, int SWymiar>
std::istream &operator>>(std::istream &stream, Wektor<STyp, SWymiar> &wektor) {
    for (int i = 0; i < SWymiar; i++) {
        float tmp;
        stream >> tmp;
        wektor[i] = tmp;
    }
    return stream;
}

template <typename STyp, int SWymiar>
std::ostream &operator<<(std::ostream &stream,Wektor<STyp, SWymiar> wektor) {
    for (int i = 0; i < ROZMIAR; i++) {
        stream << std::setw(5)<<wektor[i]<<std::endl;
    }
    std::cout << std::endl;
    return stream;
}

template <typename STyp, int SWymiar>
float oblicz_dlugosc(Wektor<STyp, SWymiar> wektor){
     return sqrt(wektor*wektor);
}
#endif
