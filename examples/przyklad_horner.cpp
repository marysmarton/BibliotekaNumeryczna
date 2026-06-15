#include "../include/horner.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout << "Program demonstracyjny - schemat hornera=" << endl;

    // Definiujemy wielomian: W(x) = 2x^3 - 5x^2 + 3x + 7
    // Współczynniki podajemy od najniższej potęgi: a0=7, a1=3, a2=-5, a3=2
    vector<double> wspolczynniki = {7.0, 3.0, -5.0, 2.0};
    
    // Punkt, dla którego liczymy wartość wielomianu, np. x = 2.0
    double x = 2.0;

    // Wywołanie funkcji z biblioteki
    double wynik = horner(wspolczynniki, x);

    cout << "Dla wielomianu W(x) = 2x^3 - 5x^2 + 3x + 7" << endl;
    cout << "Wartosc w punkcie x = " << x << " wynosi: " << wynik << endl;

    return 0;
}
