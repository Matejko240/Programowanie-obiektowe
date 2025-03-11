#include <iostream>
#include <fstream>
#include "LZespolone.hh"
#include "UkladRownanLiniowych.hh"

using namespace std;


void uklad_zespolona()
  {
  cout << endl << " Start programu " << endl << endl;
  ifstream plik;
  UkladRownanLiniowych<LZespolona, ROZMIAR> UklRown;
  plik.open("rownanie_liczb_zespolone.dat", ios::in);
  //if(!plik.good()) 
  //{ //Asercja
    //cout << "blad wczytywania pliku" << endl;
   // return 1;
  //}
  plik>>UklRown;
  plik.close();
  UklRown.rozwiaz();
  cout<<UklRown;
}
void uklad_rzeczywista()
  {
  cout << endl << " Start programu " << endl << endl;
  ifstream plik;
  UkladRownanLiniowych<float, ROZMIAR> UklRown;
  plik.open("rownanie_liczb_rzeczywistych.dat", ios::in);
  //if(!plik.good()) 
  //{ //Asercja
   // cout << "blad wczytywania pliku" << endl;
    //return 1;
  //}
  plik>>UklRown;
  plik.close();
  UklRown.rozwiaz();
  cout<<UklRown;
}
int main() 
{
  char wybor;
  cout << "wybierz czy liczby zespolone(L) czy rzeczywiste(R)" << endl;
  cin >> wybor;
  switch(wybor)
  {
    case 'L':
    {
          uklad_zespolona();
          break;
    }
        case 'R':
    {
          uklad_rzeczywista();
          break;
    }
  }
}