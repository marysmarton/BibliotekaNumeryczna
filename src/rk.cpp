#include "../include/rk.h" 
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// Funkcja zwracajaca analityczne (dokladne) rozwiazanie rownania rozniczkowego dla czasu t
double rozwiazanie_dokladne(double t)
{//przyjmuje za parametr czas t
    double T = 14935000.0 / pow((79951556409.0 * t) / 2.0 + 15625000000.0, 1.0 / 3.0);
    return T;
}

// Funkcja definiujaca pochodna dT/dt (prawo chlodzenia/promieniowania)
double pochodna(double T)
{
    double dT = 0.0;
    double beta = 0.0;
    double alfa = -4 * pow(10, -12);
    dT = alfa * (pow(T, 4) - beta); // Rownanie rozniczkowe: dT/dt = alfa * T^4
    return dT;//zwraca rownanie rozniczkowe
}

// Numeryczne rozwiazywanie rownania metoda Heuna (metoda jawna trapezow rzedu 2)
void metoda_heuna()
{
    // Konfiguracja warunkow poczatkowych i parametrow kroku czasowego
    double T0 = 5974.0; 
    double t0 = 0.0; 
    double t_end = 5974.0; 
    int n = 100000; 
    double h = t_end / n; // Dlugosc pojedynczego kroku czasowego

    vector<double> t(n + 1);
    vector<double> T(n + 1);

    t[0] = t0;
    T[0] = T0;
// Glowna petla iteracyjna metody Heuna
    for (int i = 0; i < n; i++)
    {
        t[i + 1] = t[i] + h;
        // Krok 1: Predyktor (szacowanie wartosci T w nastepnym kroku metoda Eulera)
        double T_predyktor = T[i] + h * pochodna(T[i]);
        // Krok 2: Korektor (wyznaczenie ostatecznej wartosci jako srednia z dwoch pochodnych)
        T[i + 1] = T[i] + (h / 2.0) * (pochodna(T[i]) + pochodna(T_predyktor));
    }
// Wyswietlanie tabeli z wynikami kontrolnymi (co 5000 iteracji)
    cout << "t[s]        T_Heun        T_exact\n";
    for (int i = 0; i <= n; i += n / 20)
    {
        cout << fixed << setprecision(6) << setw(8) << t[i] << "   "
             << setw(12) << T[i] << "   "
             << setw(12) << rozwiazanie_dokladne(t[i])
             << "\n";
    }
}

// Numeryczne rozwiazywanie rownania metoda punktu srodkowego (rzedu 2)
void metoda_punktu_srodkowego()
{
        // Konfiguracja warunkow poczatkowych i parametrow kroku czasowego
    double T0 = 5974.0; 
    double t0 = 0.0; 
    double t_end = 5974.0; 
    int n = 100000; 
    double h = t_end / n; 

    vector<double> t(n + 1);
    vector<double> T(n + 1);

    T[0] = T0;
    t[0] = t0;

    // Glowna petla iteracyjna metody punktu srodkowego
    for (int i = 0; i < n; i++)
    {
        t[i + 1] = t[i] + h;
        // Wyznaczenie przyblizonej wartosci temperatury w polowie biezacego kroku (t + h/2)
        double T_polowa = T[i] + 0.5 * h * pochodna(T[i]);
        // Obliczenie nowej wartosci przy uzyciu pochodnej wyznaczonej w punkcie srodkowym
        T[i + 1] = T[i] + h * pochodna(T_polowa);
    }
// Wyswietlanie tabeli porownawczej z rozwiazaniem dokladnym
    cout << "t[s]        T_srodkowy        T_exact\n";
    for (int i = 0; i <= n; i += n / 20)
    {
        cout << fixed << setprecision(6) << setw(8) << t[i] << "   "
             << setw(12) << T[i] << "   "
             << setw(12) << rozwiazanie_dokladne(t[i])
             << "\n";
    }
}

// Klasyczna metoda Rungego-Kutty czwartego rzedu (RK4) - najwyzsza dokladnosc
void metoda_kutty()
{
            // Konfiguracja warunkow poczatkowych i parametrow kroku czasowego
    double T0 = 5974.0; 
    double t0 = 0.0; 
    double t_end = 5974.0; 
    int n = 100000; 
    double h = t_end / n; 

    vector<double> t(n + 1);
    vector<double> T(n + 1);

    T[0] = T0;
    t[0] = t0;

    // Glowna petla iteracyjna algorytmu RK4
    for (int i = 0; i < n; i++)
    {
        t[i + 1] = t[i] + h;
        double k1, k2, k3, k4;
// Wyznaczanie czterech wspolczynnikow przyrostu (probkowanie pochodnej w roznych punktach kroku)
        k1 = pochodna(T[i]); // Próbka na poczatku kroku
        k2 = pochodna(T[i] + 0.5 * h * k1); // Próbka w punkcie srodkowym przy uzyciu k1
        k3 = pochodna(T[i] + 0.5 * h * k2); // Próbka w punkcie srodkowym przy uzyciu k2
        k4 = pochodna(T[i] + h * k3);// Próbka na koncu kroku przy uzyciu k3
// Wyznaczenie ostatecznej wartosci jako srednia wazona obliczonych wspolczynnikow
        T[i + 1] = T[i] + (h / 6.0) * (k1 + k4 + 2.0 * (k2 + k3));
    }
// Wyswietlanie tabeli porownawczej dla metody RK4
    cout << "t[s]        T_Kutty        T_exact\n";
    for (int i = 0; i <= n; i += n / 20)
    {
        cout << fixed << setprecision(6) << setw(8) << t[i] << "   "
             << setw(12) << T[i] << "   "
             << setw(12) << rozwiazanie_dokladne(t[i])
             << "\n";
    }
}
