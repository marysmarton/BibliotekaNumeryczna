#include "../include/calki.h" // Łączenie z nagłówkiem
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


struct dane_calki
{
    int n;             // stopien wielomianu
    double a;          // przedzial poczatek
    double b;          // przedzial koniec
    vector<double> ai; // wspolczynniki 
};


bool wczytaj_dane(string nazwa, dane_calki &dane) 
{
    string tekst;
    ifstream plik(nazwa);

    if (!plik.is_open())
    {
        cerr << "Nie udalo sie otworzyc pliku: " << nazwa << endl;
        return false;
    }

    // n - stopien wielomianu
    plik >> tekst >> tekst >> tekst >> tekst >> dane.n; // pominiecie napisów itp.
    plik >> tekst;

    // wczytywanie wspolczynnikow wielomianu
    for (int i = 0; i <= dane.n; i++)
    {
        double p;
        if (plik >> p)
        {
            dane.ai.push_back(p);
        }
    }

    plik >> tekst;

    // wczytywanie granic przedzialu
    plik >> dane.a >> dane.b;

    plik.close();
    return true;
}


void metoda_calkowania()
{
  
    string nazwa = "data/calka.txt"; 
    dane_calki moje_dane;

    if (wczytaj_dane(nazwa, moje_dane))
    {
        cout << endl << "Wczytane dane do calkowania: " << endl;
        cout << "Stopien wielomianu: " << moje_dane.n << endl;
        cout << "Przedzial od: " << moje_dane.a << " do: " << moje_dane.b << endl;
        
        cout << "Wspolczynniki: ";
        for (double wsp : moje_dane.ai) 
        {
            cout << wsp << " ";
        }
        cout << endl;

        // dodac tutaj metody trapezow i metody simpsona
        // Np. double wynik = oblicz_trapezy(moje_dane);
        // cout << "Wynik calkowania: " << wynik << endl;
    }
}
