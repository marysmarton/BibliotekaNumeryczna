#include "../include/euler.h" 
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// Funkcja zwracająca rozwiązanie dokładne równania różniczkowego
// Rozwiązanie dokładne z wyliczoną funkcją z WolframAlpha
//przyjmuje parametr t dla ktorego jest obliczana wartosc funkcji
double rozwiazanie_dokladne_euler(double t)
{
    double T = 14935000.0 / pow((79951556409.0 * t) / 2.0 + 15625000000.0, 1.0 / 3.0);
    return T; //funkcja zwraca wartosc funkcji w punkcie t
}

// Funkcja wyznaczająca pochodną T'
// Funkcja obliczająca pochodną T' zgodnie z równaniem różniczkowym
//przyjmuje funkcje T
double pochodna_euler(double T)
{
    double dT = 0.0;
    double beta = 0.0;
    double alfa = -4 * pow(10, -12);
    dT = alfa * (pow(T, 4) - beta);
    return dT; //funkcja zwraca pochodna
}

// Główna funkcja wywoływana z menu, realizująca metodę Eulera
void metoda_eulera()
{
    double T0 = 5974.0;    // temperatura początkowa
    double t0 = 0.0;       // czas początkowy
    double t_end = 5974.0; // czas końcowy
    int n = 1000000;       // liczba kroków
    double h = t_end / n;  // krok czasowy

    vector<double> t(n + 1);
    vector<double> T(n + 1);

    // Inicjalizacja warunków początkowych
    t[0] = t0;
    T[0] = T0;

    double suma_kwadratow_bledow = 0.0;

    // Pętla metody Eulera wraz z jednoczesnym liczeniem błędów
    // Iteracyjne wyznaczanie rozwiązania metodą Eulera
    for (int i = 0; i < n; i++)
    {
        t[i + 1] = t[i] + h;
        T[i + 1] = T[i] + h * pochodna_euler(T[i]);
        
        // Obliczanie błędu dla obecnego kroku
        // Obliczenie błędu względem rozwiązania dokładnego
        double w_dokladna = rozwiazanie_dokladne_euler(t[i + 1]);
        double blad = w_dokladna - T[i + 1];
        suma_kwadratow_bledow += blad * blad;
    }

    // Średnia błędów kwadratowych
    double sredni_blad_kwadratowy = suma_kwadratow_bledow / (n + 1);

    // Drukowanie tabeli wyników
    // Wyświetlenie wyników w formie tabeli
    cout << "t[s]        T_Euler        T_exact\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i <= n; i += n / 20)
    {
        cout << fixed << setprecision(6) << setw(8) << t[i] << "   "
             << setw(12) << T[i] << "   "
             << setw(12) << rozwiazanie_dokladne_euler(t[i])
             << "\n";
    }

    // Wyświetlenie statystyk błędu z komentarza w kodzie
    cout << "-------------------------------------------\n";
    cout << "STATYSTYKA BLEDOW:\n";
    cout << "Sredni blad kwadratowy (MSE): " << scientific << setprecision(6) << sredni_blad_kwadratowy << endl;
}
