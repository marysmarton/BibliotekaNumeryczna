#include "../include/newton.h" 
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

//pierwsza funkcja testowa
double funkcja1_newton(double x)
{
    return exp(-x) * sin(x) + x / 5.0;
}

//druga funkcja testowa
double funkcja2_newton(double x)
{
    return ((x + 1.0) * (x - 1.0)) / (pow(x, 2.0) + 1.0) + 0.2 * cos(x);
}

//trzecia funkcja testowa
double funkcja3_newton(double x)
{
    return sin(x) * log(pow(x, 2.0) + 1.0);
}

//analityczna pochodna pierwszej funkcji
double pochodna1(double x)
{
    return exp(-x) * (cos(x) - sin(x)) + 0.2;
}

//analityczna pochodna drugiej funkcji
double pochodna2(double x)
{
    return (4.0 * x - 0.2 * pow((pow(x, 2.0) + 1.0), 2.0) * sin(x)) / pow((pow(x, 2.0) + 1.0), 2.0);
}

//analityczna pochodna trzeciej funkcji
double pochodna3(double x)
{
    return (2.0 * x * sin(x)) / (pow(x, 2.0) + 1.0) + log(pow(x, 2.0) + 1.0) * cos(x);
}

//Algorytm szukania miejsca zerowego metoda Newtona (stycznych) przy uzyciu pochodnej
bool metoda_newtona(int n, double x0, double &wynik, double (*f)(double), double(*df)(double))
{
    double x = x0;
    double dokladnosc = 1e-7;// Warunek zakonczenia obliczen (Epsilon)

    cout << fixed << setprecision(6);
    cout << "  Punkt startowy: " << x0 << endl; 
// Glowna petla iteracyjna metody Newtona
    for (int i = 0; i < n; i++)
    {
        double fx = f(x);
        double dfx = df(x);

        // Zabezpieczenie przed dzieleniem przez zero (gdy styczna jest rownolegla do osi OX)
        if (abs(dfx) < 1e-12)
        {
            cout << "  Blad: pochodna bliska zeru - przerwanie." << endl;
            return false;
        }
// Wzor rekurencyjny metody Newtona: x_{i+1} = x_i - f(x_i)/f'(x_i)
        double x_next = x - fx / dfx;

        cout << "  Iteracja " << i + 1 << ": x = " << x_next << endl;
        // Sprawdzenie kryterium zakonczenia na podstawie odleglosci miedzy kolejnymi przyblizeniami
        if (abs(x_next - x) < dokladnosc)
        {
            cout << "  Osiagnieto wymagana dokladnosc!" << endl;
            wynik = x_next; // Zapisanie wyniku koncowego pod referencje
            return true;
        }
        x = x_next; // Przejscie do kolejnego kroku
    }

    cout << "  Osiagnieto limit iteracji bez zbieznosci." << endl;
    return false;  
}

// Algorytm szukania miejsca zerowego metoda siecznych (nie wymaga znajomosci pochodnej funkcji)
bool metoda_siecznych(int n, double x0, double x1, double &wynik, double(*f)(double))
{
    double dokladnosc = 1e-7;
    double x_before = x0;  // Punkt x_{i-1}
    double x_now = x1; // Punkt x_i

    cout << "  Krok 0: x0 = " << x0 << endl;
    cout << "  Krok 1: x1 = " << x1 << endl;
// Glowna petla iteracyjna metody siecznych
    for (int i = 0; i < n; i++)
    {
        double fx_before = f(x_before);
        double fx_now = f(x_now);
// Zabezpieczenie przed dzieleniem przez zero (gdy wartosci funkcji w obu punktach sa takie same)
        if (abs(fx_now - fx_before) < 1e-12)
        {
            cout << "  Blad: mianownik bliski zeru - przerwanie." << endl;
            return false;
        }
// Wzor metody siecznych aproksymujacy pochodna roznica wartosci na koncach przedzialu
        double x_next = x_now - fx_now * (x_now - x_before) / (fx_now - fx_before);

        cout << "  Krok " << i + 2 << ": x = " << x_next << endl;
// Sprawdzenie kryterium stopu
        if (abs(x_next - x_now) < dokladnosc)
        {
            cout << "  Osiagnieto dokladnosc i znaleziono rozwiazanie!" << endl;
            wynik = x_next;
            return true;
        }
// Przesuniecie punktow do nastepnego kroku iteracji
        x_before = x_now;
        x_now = x_next;
    }

    cout << "  Osiagnieto limit iteracji bez zbieznosci." << endl;
    return false;
}

// Glowna funkcja koordynujaca, ktora uruchamia testy porownawcze obu metod dla wszystkich 3 funkcji
void uruchom_metody_newtona_i_siecznych(double x0, int n)
{
    double wynik;
    double x1 = x0 + 0.1; // Wyznaczenie drugiego punktu startowego dla metody siecznych

    cout << fixed << setprecision(6);
    
    cout << "=========================================" << endl;
    cout << "METODA NEWTONA (STYCZNYCH)" << endl;
    cout << "=========================================" << endl;

    cout << "\n--- Funkcja 1 ---" << endl;
    if (metoda_newtona(n, x0, wynik, funkcja1_newton, pochodna1)) cout << "-> Wynik koncowy: Pierwiastek = " << wynik << endl;
    else cout << "-> Wynik koncowy: Nie znaleziono pierwiastka." << endl;

    cout << "\n--- Funkcja 2 ---" << endl;
    if (metoda_newtona(n, x0, wynik, funkcja2_newton, pochodna2)) cout << "-> Wynik koncowy: Pierwiastek = " << wynik << endl;
    else cout << "-> Wynik koncowy: Nie znaleziono pierwiastka." << endl;

    cout << "\n--- Funkcja 3 ---" << endl;
    if (metoda_newtona(n, x0, wynik, funkcja3_newton, pochodna3)) cout << "-> Wynik koncowy: Pierwiastek = " << wynik << endl;
    else cout << "-> Wynik koncowy: Nie znaleziono pierwiastka." << endl;

    cout << "\n=========================================" << endl;
    cout << "METODA SIECZNYCH" << endl;
    cout << "=========================================" << endl;

    cout << "\n--- Funkcja 1 ---" << endl;
    if (metoda_siecznych(n, x0, x1, wynik, funkcja1_newton)) cout << "-> Wynik koncowy: Pierwiastek = " << wynik << endl;
    else cout << "-> Wynik koncowy: Nie znaleziono pierwiastka." << endl;

    cout << "\n--- Funkcja 2 ---" << endl;
    if (metoda_siecznych(n, x0, x1, wynik, funkcja2_newton)) cout << "-> Wynik koncowy: Pierwiastek = " << wynik << endl;
    else cout << "-> Wynik koncowy: Nie znaleziono pierwiastka." << endl;

    cout << "\n--- Funkcja 3 ---" << endl;
    if (metoda_siecznych(n, x0, x1, wynik, funkcja3_newton)) cout << "-> Wynik koncowy: Pierwiastek = " << wynik << endl;
    else cout << "-> Wynik koncowy: Nie znaleziono pierwiastka." << endl;
}
