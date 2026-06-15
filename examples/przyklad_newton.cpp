#include "../include/newton.h"
#include <iostream>

using namespace std;

// Prosta funkcja testowa, dla ktorej znamy miejsce zerowe (np. x = 2)
double prosta_funkcja(double x)
{
    return x * x - 4.0; // x^2 - 4
}

// Pochodna tej funkcji
double prosta_pochodna(double x)
{
    return 2.0 * x; // 2x
}

int main()
{
    cout << "Program demonstracyjny - metoda Newtona" << endl;

    int max_iteracji = 20;
    double punkt_startowy = 6.0;
    double znaleziony_pierwiastek = 0.0;

    // Wywołanie algorytmu Newtona 
    bool sukces = metoda_newtona(max_iteracji, punkt_startowy, znaleziony_pierwiastek, prosta_funkcja, prosta_pochodna);

    if (sukces)
    {
        cout << "Znaleziono miejsce zerowe funkcji x^2 - 4" << endl;
        cout << "Wynik to: " << znaleziony_pierwiastek << endl;
    }
    else
    {
        cout << "Algorytm nie zdolal znalezc miejsca zerowego." << endl;
    }

    return 0;
}
