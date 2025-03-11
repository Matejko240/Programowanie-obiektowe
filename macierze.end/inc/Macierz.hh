#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "Wektor.hh"
#include "rozmiar.h"
#include "LZespolone.hh"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <cmath>
#include <algorithm>

/*
 *  Tutaj trzeba opisac klase. Jakie pojecie modeluje ta klasa
 *  i jakie ma glowne cechy.
 */
template <typename STyp, int SWymiar>
class Macierz {
  Wektor<STyp, SWymiar> dane[SWymiar];
  STyp wyznacznik;
  /*
   *  Tutaj trzeba wstawic definicje odpowiednich pol i metod prywatnych
   */
  public:
  STyp det() const; //obliczanie wyznacznika
  const STyp &operator()(int i, int j) const;
  //przeciazenie w celu ulatwienia operacji
  STyp &operator()(int i, int j) {
    assert(i >= 0 && i < SWymiar && j >= 0 && j < SWymiar);
    return dane[j][i];
  }
 void kopiuj_dane(STyp array[][SWymiar]) const;
  //transpozycja
  void transpozycja();
  //mnozenie macierzy
  Wektor<STyp, SWymiar> operator*(const Wektor<STyp, SWymiar> wektor) const;
  //zmiana kolumn 
  void zmiana_kol(int ktora, Wektor<STyp, SWymiar> kolumna);
  //
  /*
   *  Tutaj trzeba wstawic definicje odpowiednich metod publicznych
   */    
};

template <typename STyp, int SWymiar>
const STyp &Macierz<STyp, SWymiar>::operator()(int i, int j) const {
    assert(i >= 0 && i < SWymiar && j >= 0 && j < SWymiar);
    return dane[j][i];
}
//Przeciazenie wczytywania dla macierzy
template <typename STyp, int SWymiar>
std::istream &operator>>(std::istream &stream, Macierz<STyp, SWymiar> &Macierz) {
    for (int i = 0; i < SWymiar; i++) {
        for (int j = 0; j < SWymiar; j++) {
            STyp tmp = 0;
            stream >> tmp;
            Macierz(i, j) = tmp;
        }
    }
    return stream;
}

//Przeciazenie wypisywania dla macierzy
template <typename STyp, int SWymiar>
std::ostream &operator<<(std::ostream &stream, const Macierz<STyp, SWymiar> &Macierz) {
    for (int i = 0; i < SWymiar; i++) {
        for (int j = 0; j < SWymiar; j++) {
            stream << std::setw(8) << Macierz(i, j);
        }
        std::cout << std::endl;
    }
    return stream;
}

//Obliczanie wyznacznika metodą Gaussa
template <typename STyp, int SWymiar>
STyp Macierz<STyp, SWymiar>::det() const {
    STyp det = {1};
    STyp tmp[SWymiar][SWymiar];
    kopiuj_dane(tmp);
    for (int i = 0; i < SWymiar; i++) {
        if (abs(tmp[i][i]) < EPSILON) {
            int j;
            for (j = i + 1; j < SWymiar; j++)
                if (abs(tmp[j][i]) > EPSILON ) {
                    for (int k = i; k < SWymiar; k++) {
                        STyp aux = tmp[i][k];
                        tmp[i][k] = tmp[j][k];
                        tmp[j][k] = aux;
                    }
                    det *= (-1);
                    break;
                }
            if (j == SWymiar)
                det = 0;
        }
        for (int j = i + 1; j < SWymiar; j++) {
            if (abs(tmp[j][i]) < EPSILON)
                continue;
            STyp a = tmp[j][i] / tmp[i][i];
            for (int k = i + 1; k < SWymiar; k++) {
                tmp[j][k] -= a * tmp[i][k];
            }

        }
    }
    for (int i = 0; i < SWymiar; i++) {
        det *= tmp[i][i];
    }
    return det;
}

template <typename STyp, int SWymiar>
void Macierz<STyp, SWymiar>::transpozycja() {
    STyp tmp[SWymiar][SWymiar];
    for (int i = 0; i < SWymiar; i++) {
        for(int j = 0; j < SWymiar; j++) {
            tmp[i][j] = this->dane[i][j];
        }
    }
    for (int i = 0; i < SWymiar; i++){
        for (int j=0; j < SWymiar; j++) {
            std::swap(this->dane[j][i], tmp[i][j]);
        }
    }
}

template <typename STyp, int SWymiar>
void Macierz<STyp, SWymiar>::zmiana_kol(int ktora, Wektor<STyp, SWymiar> kolumna) {
    assert(ktora >= 0 && ktora < SWymiar);
    std::swap(this->dane[ktora], kolumna); //swap to zmiana
}
//Mnozenie macierzy przez wektor
template <typename STyp, int SWymiar>
Wektor<STyp, SWymiar> Macierz<STyp, SWymiar>::operator*(const Wektor<STyp, SWymiar> wektor) const {
    Wektor<STyp, SWymiar> wynik;
    STyp tmp[SWymiar][SWymiar];
    this->kopiuj_dane(tmp);
    for (int i = 0; i < SWymiar; i++) {
        for (int j = 0; j < SWymiar; j++) {
            wynik[i] += wektor[j] * tmp[i][j];
        }
    }
    return wynik;
}

/*Zdefiniowanie pomocnej funkcji kopiujacej zawartosc macierzy
 * do tablicy dwuwymiarowej*/
template <typename STyp, int SWymiar>
void Macierz<STyp, SWymiar>::kopiuj_dane(STyp array[][SWymiar]) const {
    for (int i = 0; i < ROZMIAR; i++) {
        for (int j = 0; j < ROZMIAR; j++) {
            array[i][j] = this->dane[i][j];
        }
    }
}

#endif
