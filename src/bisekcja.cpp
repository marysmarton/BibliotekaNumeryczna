#include "../include/bisekcja.h" 
#include <iostream>
#include <numeric>
#include <cmath>

using namespace std;

//funkcja testowa 1, przyjmuje parametr x dla ktorego bedzie obliczana wartosc funkcji
double funkcja1(double x)
{
    double funkcja = pow(x, 6.0) - 9.0 * pow(x, 5.0) + 29.0 * pow(x, 4.0) - 39 * pow(x, 3.0) + 23.0 * pow(x, 2.0) - 6.0 * x - 3.0;
    return funkcja;
}

//funkcja testowa 2, przyjmuje parametr x dla ktorego bedzie obliczana wartosc funkcji
double funkcja2(double x)
{
    double funkcja = pow(x, 3.0) + cos(x) - 1.0 / x;
    return funkcja;
}

//funkcja testowa 3, przyjmuje parametr x dla ktorego bedzie obliczana wartosc funkcji
double funkcja3(double x)
{
    double funkcja = 2.0 * sin(x) * cos(pow(x, 2.0));
    return funkcja;
}

// Algorytm bisekcji - wyznaczanie miejsca zerowego poprzez wielokrotne dzielenie przedzialu na polowy
//przyjmuje: n - liczba podzialow miedzy a i b, a - poczatek przedzialu, b - koniec przedzialu, epsilon - tolerancja bledu
double bisekcja(int n, double a, double b, double epsilon)
{
    double f_a = funkcja1(a);
    double f_b = funkcja1(b);

    //sprawdzenie zmiany znaku na koncach przedzialu
    if (f_a * f_b >= 0)
    {
        cout << "Funkcja nie zmienia znaku na koncach przedzialu!" << endl;
        return NAN;
    }

    double c = 0.0;

    //glowna petla algorytmu
    for (int i = 0; i < n; i++)
    {
        //wyznaczanie srodka przedzialu
        c = (a + b) / 2.0;
        double f_c = funkcja1(c);

        cout << "Iteracja nr: " << i + 1 << endl;
        cout << "Punkt przeciecia z osia OX: " << c << endl;

        // Warunki stopu (zkaonczenia)
        if (f_c == 0 || (b - a) / 2.0 < epsilon)
        {
            cout << "Osiagnieto maksymalna dokladnosc przedzialu." << endl;
            cout << "Koncowo przyblizone miejsce zerowe wynosi: " << c << endl;
            return c;
        }

        // Aktualizacja przedziału
        if (f_a * f_c < 0)
        {
            b = c;
            f_b = f_c;
        }
        else
        {
            a = c;
            f_a = f_c;
        }
    }

    cout << "Koncowo przyblizone miejsce zerowe wynosi: " << c << endl;
    return c;
}

// Algorytm falszywej linii (Regula Falsi)
// Metoda fałszywej linii (Regula Falsi) - wyznaczanie miejsca zerowego
// poprzez przecięcie siecznej z osią OX.
//podobnie przyjmuje parametry jak metoda bisekcji
double false_line(int n, double a, double b, double epsilon)
{
    double f_a = funkcja1(a);
    double f_b = funkcja1(b);

      // Sprawdzenie zmiany znaku na końcach przedziału
    if (f_a * f_b >= 0)
    {
        cout << "Funkcja nie zmienia znaku na koncach przedzialu!" << endl;
        return NAN;
    }

    double x_i = 0.0;

     // Główna pętla algorytmu
    for (int i = 0; i < n; i++)
    {
        // Wyznaczenie punktu przecięcia siecznej z osią OX
        double wspolczynnik_kierunkowy = (f_b - f_a) / (b - a);
        double wyraz_wolny = f_b - wspolczynnik_kierunkowy * b;
        x_i = -wyraz_wolny / wspolczynnik_kierunkowy;

        double f_xi = funkcja1(x_i);

        cout << "Iteracja nr " << i + 1 << endl;
        cout << "Przyblizenie pierwiastka x1 - przeciecie z osia OX: " << x_i << endl;
        cout << "Rownanie prostej: y = " << wspolczynnik_kierunkowy << "x + " << wyraz_wolny << endl;

        // Warunki stopu
        // Sprawdzenie warunku zakończenia
        if (fabs(f_xi) < epsilon || fabs(b - a) < epsilon)
        {
            cout << "Osiagnieto maksymalna dokladnosc przedzialu." << endl;
            return x_i;
        }

        // Aktualizacja przedziału
        if (f_a * f_xi < 0)
        {
            b = x_i;
            f_b = f_xi;
        }
        else
        {
            a = x_i;
            f_a = f_xi;
        }
    }

    return x_i;
}
