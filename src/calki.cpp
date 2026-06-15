#include "../include/calki.h" // Łączenie z nagłówkiem
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// Struktura przechowująca dane potrzebne do obliczenia całki:
// stopień wielomianu, współczynniki oraz granice całkowania.
struct dane_calki
{
    int n;             // stopien wielomianu
    double a;          // przedzial poczatek
    double b;          // przedzial koniec
    vector<double> ai; // wspolczynniki 
};

// Funkcja obliczająca wartość wielomianu w punkcie x na podstawie wczytanych danych
// Oblicza wartość wielomianu w punkcie x
// na podstawie współczynników wczytanych z pliku.
//przyjmuje dane calki przez referencje oraz x dla ktorego jest obliczana wartosc wielomianu
double oblicz_wartosc_wielomianu(double x, const dane_calki &dane)
{
    double wynik = 0.0;
    for (int i = 0; i <= dane.n; i++)
    {
        wynik += dane.ai[i] * pow(x, i);
    } //funkcja zwraca wartosc wielomianu w tym punkcie
    return wynik;
}

// Oblicza całkę metodą kwadratury Gaussa
// dla 2-, 3- lub 4-punktowej reguły.
// Dwupunktowa, trzypunktowa i czteropunktowa kwadratura Gaussa zaadaptowana dla wielomianu
//przyjmuje dane calki przez referencje a takze a - poczatek przedzialu b - koniec przedzialu n - stopien wielomianu)
double GaussWielomian(double a, double b, int n, const dane_calki &dane)
{
    // Wyznaczenie środka i połowy długości przedziału
    double srodek = (a + b) / 2.0; 
    double polowa = (b - a) / 2.0; 
    double wynik = 0.0;

    //dwupunktowa kwadratura Gaussa
    if (n == 2)
    {
        double x1 = 0.5773502692;
        wynik = polowa * (oblicz_wartosc_wielomianu(polowa * (-x1) + srodek, dane) + 
                          oblicz_wartosc_wielomianu(polowa * x1 + srodek, dane)); 
    }
        //trzypunktowa kwadratura Gaussa
    else if (n == 3)
    {
        double x2 = 0.7745966692;
        double w1 = 5.0 / 9.0;
        double w2 = 8.0 / 9.0;
        wynik = polowa * (w1 * oblicz_wartosc_wielomianu(polowa * (-x2) + srodek, dane) + 
                          w1 * oblicz_wartosc_wielomianu(polowa * x2 + srodek, dane) + 
                          w2 * oblicz_wartosc_wielomianu(srodek, dane)); 
    }
        //czteropunktowa kwadratura Gaussa
    else if (n == 4) 
    {
        double x3 = 0.3399810436;
        double x4 = 0.8611363116;
        double w3 = 0.6521451549;
        double w4 = 0.3478548451;
        wynik = polowa * (w3 * oblicz_wartosc_wielomianu(polowa * (-x3) + srodek, dane) + 
                          w3 * oblicz_wartosc_wielomianu(polowa * x3 + srodek, dane) + 
                          w4 * oblicz_wartosc_wielomianu(polowa * (-x4) + srodek, dane) + 
                          w4 * oblicz_wartosc_wielomianu(polowa * x4 + srodek, dane));
    }
//funkcja zwraca wartosc calki obliczonej metoda kwadratury gaussa dla zadanych parametrow
    return wynik;
}

// Kwadratura złożona Gaussa dla wielomianu
// Realizacja złożonej kwadratury Gaussa
// poprzez podział przedziału na mniejsze części.
//przyjmuje granice przedzialu a i b, liczbe przedzialow, dane calki w postaci referencji
// n - liczba wezlow kwadratury Gaussa
double kwadratura_zlozona_wielomian(double a, double b, int liczba_przedzialow, int n, const dane_calki &dane)
{
    double suma = 0.0;
    double h = (b - a) / liczba_przedzialow; 
    for (int i = 0; i < liczba_przedzialow; i++)
    {
        double start = a + i * h; 
        double koniec = start + h; 
        suma += GaussWielomian(start, koniec, n, dane);
    } //funkcja zwraca wartosc wielomianu
    return suma;
}

// Metoda Simpsona dopasowana do struktury danych wielomianu
// Obliczanie całki metodą Simpsona.
//przyjmuje granice przedzialu a i b, liczbe przedzialow, dane calki w postaci referencji
double SimpsonCalkiWielomian(double a, double b, int n_przedzialow, const dane_calki &dane)
{
    if (n_przedzialow % 2 != 0)
    {
        n_przedzialow++;
    }

    // Podział całki na mniejsze przedziały
    double h = (b - a) / n_przedzialow;
    double suma = oblicz_wartosc_wielomianu(a, dane) + oblicz_wartosc_wielomianu(b, dane);

    for (int i = 1; i < n_przedzialow; i++)
    {
        // Metoda Simpsona wymaga parzystej liczby przedziałów
        double x = a + i * h;
        if (i % 2 == 0)
        {
            suma += 2 * oblicz_wartosc_wielomianu(x, dane);
        }
        else
        {
            suma += 4 * oblicz_wartosc_wielomianu(x, dane);
        }
    }
    //funkcja zwraca wartosc calki obliczonej metoda simpsona
    return (h / 3.0) * suma;
}

// Metoda trapezów dopasowana do struktury danych wielomianu
//przyjmuje granice przedzialow a i b, liczbe przedzialow, dane calki w postaci referencji
double metoda_trapezow_wielomian(double a, double b, int n_przedzialow, const dane_calki &dane) 
{
    double h = (b - a) / n_przedzialow;
    double suma = 0.5 * (oblicz_wartosc_wielomianu(a, dane) + oblicz_wartosc_wielomianu(b, dane));
    
    for (int i = 1; i < n_przedzialow; i++)
    {
        double x = a + i * h;
        suma += oblicz_wartosc_wielomianu(x, dane);
    }
    return suma * h;
}

// Wczytuje stopień wielomianu, współczynniki
// oraz granice całkowania z pliku tekstowego.
//przyjmuje nazwe pliku tesktowego oraz dane calki w postaci referencji
bool wczytaj_dane(string nazwa, dane_calki &dane) 
{
    string tekst;
    ifstream plik(nazwa);

    if (!plik.is_open())
    {
        cerr << "Nie udalo sie otworzyc pliku: " << nazwa << endl;
        return false;
    }

    plik >> tekst >> tekst >> tekst >> tekst >> dane.n; 
    plik >> tekst;

    for (int i = 0; i <= dane.n; i++)
    {
        double p;
        if (plik >> p)
        {
            dane.ai.push_back(p);
        }
    }

    plik >> tekst;
    plik >> dane.a >> dane.b;

    plik.close();
    return true;
}

// Funkcja główna modułu całkowania:
// wczytuje dane z pliku i porównuje wyniki
// różnych metod całkowania numerycznego.
void metoda_calkowania()
{
    string nazwa = "data/calka.txt"; 
    dane_calki moje_dane;

    if (wczytaj_dane(nazwa, moje_dane))
    {
        cout << fixed << setprecision(6);
        cout << "=========================================" << endl;
        cout << "Wczytane dane do calkowania: " << endl;
        cout << "=========================================" << endl;
        cout << "Stopien wielomianu: " << moje_dane.n << endl;
        cout << "Przedzial od: " << moje_dane.a << " do: " << moje_dane.b << endl;
        
        cout << "Wspolczynniki: ";
        for (double wsp : moje_dane.ai) 
        {
            cout << wsp << " ";
        }
        cout << endl << string(41, '-') << endl << endl;

        // Pobieramy granice bezpośrednio z wczytanego pliku tekstowego
        double a = moje_dane.a;
        double b = moje_dane.b;

        cout<< endl<< "Obliczenia - wielomian z pliku:" << endl;
        cout << "=========================================" << endl;
        cout << "Wynik Gauss dla n=2: " << GaussWielomian(a, b, 2, moje_dane) << endl;
        cout << "Wynik Gauss dla n=3: " << GaussWielomian(a, b, 3, moje_dane) << endl;
        cout << "Wynik Gauss dla n=4: " << GaussWielomian(a, b, 4, moje_dane) << endl;
        
        cout << "\nGauss n=2 (10 przedzialow):  " << kwadratura_zlozona_wielomian(a, b, 10, 2, moje_dane) << endl;
        cout << "Gauss n=3 (10 przedzialow):  " << kwadratura_zlozona_wielomian(a, b, 10, 3, moje_dane) << endl;
        cout << "Gauss n=4 (10 przedzialow):  " << kwadratura_zlozona_wielomian(a, b, 10, 4, moje_dane) << endl;
        
        cout << "\nGauss n=2 (100 przedzialow): " << kwadratura_zlozona_wielomian(a, b, 100, 2, moje_dane) << endl;
        cout << "Gauss n=3 (100 przedzialow): " << kwadratura_zlozona_wielomian(a, b, 100, 3, moje_dane) << endl;
        cout << "Gauss n=4 (100 przedzialow): " << kwadratura_zlozona_wielomian(a, b, 100, 4, moje_dane) << endl;
        
        cout << "\nMetoda trapezow (100 przedz.): " << metoda_trapezow_wielomian(a, b, 100, moje_dane) << endl;
        cout << "Metoda Simpsona (100 przedz.): " << SimpsonCalkiWielomian(a, b, 100, moje_dane) << endl;
    }
}
