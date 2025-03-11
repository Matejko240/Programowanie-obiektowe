#ifndef UKLADROWNANLINIOWYCH_HH
#define UKLADROWNANLINIOWYCH_HH

#include <iostream>
#include <iomanip>
#include "rozmiar.h"
#include "Wektor.hh"
#include "Macierz.hh"
#include "LZespolone.hh"
#include <cmath>
/*
 *  Tutaj trzeba opisac klase. Jakie pojecie modeluje ta klasa
 *  i jakie ma glowne cechy.
 */
template <typename STyp, int SWymiar>
class UkladRownanLiniowych {
  Macierz<STyp, SWymiar> macierz_wspolczynniki;
  STyp glowny_wyzn;
  Wektor<STyp, SWymiar> wek_wolny;
  Wektor<STyp, SWymiar> rozwiazania;
  Wektor<STyp, SWymiar> wyznaczniki;

  public:
  friend std::istream& operator >> (std::istream &stream, UkladRownanLiniowych<STyp, SWymiar> &UklRown) {
  Macierz<STyp, SWymiar> tmp;
    for (int i = 0; i < SWymiar; i++) {
        for (int j = 0; j < SWymiar; j++) {
            stream >> tmp(i, j);
        }
    }
    //Wczytanie wektora wyrazow wolnych
    for (int k = 0; k < SWymiar; k++) {
        stream >> UklRown.wek_wolny[k];
    }
    //transpozycja macierzy tymczasowej
    tmp.transpozycja();
    //Wstawienie danych do macierzy ukladu
    UklRown.macierz_wspolczynniki = tmp;
    return stream;
}
//Wypisywanie rozwiazania ukladu rownan
friend std::ostream &operator<<(std::ostream &stream, const UkladRownanLiniowych<STyp, SWymiar> &UklRown) {
    stream << "Macierz wspolczynnikow" << std::endl;
    Macierz<STyp, SWymiar> tmp;
    tmp = UklRown.macierz_wspolczynniki;
    stream<<tmp;
    stream<<std::endl<<"Wektor wyrazow wolnych"<<std::endl;
    stream<<UklRown.wek_wolny;
    stream<<std::endl<<"Glowny wyznacznik"<<std::endl;
    stream<<UklRown.glowny_wyzn;
    stream<<std::endl<<"Wektor wyznacznikow"<<std::endl;
    stream<<std::setprecision(4)<<UklRown.wyznaczniki;
    stream<<std::endl<<"Wektor rozwiazan"<<std::endl;
    stream<<std::setprecision(4)<<UklRown.rozwiazania;
    stream << "Glowne rozwiazania: " << std::endl;
       for (int i = 0; i < SWymiar; i++) 
         {
      stream << std::setprecision(4) << "x" << i + 1 << " = " << UklRown.rozwiazania[i] << std::endl;
         }
    return stream;
}
void Cramer();
void rozwiaz();   
};

//Funckja obliczajaca wyznaczniki macierzy po zamianie kolumn
template <typename STyp, int SWymiar> 
void UkladRownanLiniowych<STyp, SWymiar>::Cramer() {
    for (int i = 0; i < SWymiar; i++) {
        Macierz<STyp, SWymiar> tmp = macierz_wspolczynniki;
        tmp.zmiana_kol(i, wek_wolny);
        wyznaczniki[i] = tmp.det();
    }
}

//Funckcja rozwiazujaca uklad
template <typename STyp, int SWymiar> 
void UkladRownanLiniowych<STyp, SWymiar>::rozwiaz() {
    //Obliczenie wyznacznikow
    this->Cramer();
    //Obliczenie wyznacznika glownego
    this->glowny_wyzn = macierz_wspolczynniki.det();
    //3.Sprawdzamy czy nie dzielimy przez 0
    if(abs(glowny_wyzn)<EPSILON){
        std::cout<<"brak rozwiazania"<<std::endl;
    } else {
        //Obliczenie rozwiazan i zapisanie ich w wektorze
        for (int i = 0; i < SWymiar; i++) {
            rozwiazania[i] = (wyznaczniki[i] / glowny_wyzn);
        }
    }
}  




#endif
