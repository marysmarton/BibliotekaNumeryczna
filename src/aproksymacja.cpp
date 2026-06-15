#include "../include/aproksymacja.h" 
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

// Funkcja aproksymowana (wewnętrzna)
double funkcja_podstawowa(double x)
{
    return exp(x) * sin(5 * x) - pow(x, 3);
}

// Eliminacja Gaussa do obliczania układu równań AX=B
vector<double> gaussSolveAproksymacja(vector<vector<double>> A, vector<double> b)
{
    int n = A.size();

    for (int i = 0; i < n; i++)
    {
        int maxRow = i;
        for (int k = i + 1; k < n; k++)
        {
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
            {
                maxRow = k;
            }
        }

        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        if (fabs(A[i][i]) < 1e-12)
        {
            cout << "Macierz osobliwa - brak rozwiazania" << endl;
            return vector<double>();
        }

        for (int k = i + 1; k < n; k++)
        {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++)
            {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = b[i];
        for (int j = i + 1; j < n; j++)
        {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }

    return x;
}

// Metoda Simpsona do obliczania całek pomocniczych
double SimpsonAproksymacja(double a, double b, int n, function<double(double)> f)
{
    if (n % 2 != 0)
    {
        n++;
    }

    double h = (b - a) / n;
    double suma = f(a) + f(b);

    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        if (i % 2 == 0)
        {
            suma += 2 * f(x);
        }
        else
        {
            suma += 4 * f(x);
        }
    }

    return (h / 3.0) * suma;
}

// Generowanie macierzy i wyznaczanie wektora współczynników
vector<double> wykonaj_aproksymacje(function<double(double)> f, double a, double b, int stopien, int simpsonN)
{
    int m = stopien + 1;
    vector<vector<double>> A(m, vector<double>(m, 0.0));
    vector<double> prawe(m, 0.0);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            A[i][j] = SimpsonAproksymacja(a, b, simpsonN, [=](double x)
                {
                    return pow(x, i + j);
                });
        }

        prawe[i] = SimpsonAproksymacja(a, b, simpsonN, [=](double x)
            {
                return f(x) * pow(x, i);
            });
    }

    cout << "Macierz - sprawdzenie czy jest symetryczna: " << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(15) << fixed << setprecision(4) << A[i][j] << " ";
        }
        cout << endl;
    }

    return gaussSolveAproksymacja(A, prawe);
}

// Wyznaczanie wartości wielomianu w punkcie x
double oblicz_wielomian_aproksymacji(double x, const vector<double>& a)
{
    double wynik = 0.0;
    for (int i = 0; i < a.size(); i++)
    {
        wynik += a[i] * pow(x, i);
    }
    return wynik;
}

// Główna funkcja wywoływana przez menu główne (case 8)
void metoda_aproksymacji()
{
    // Przedziały całki i konfiguracja struktury wielomianu
    double a = 8.0;
    double b = 10.0;
    int stopien = 5;
    int simpsonN = 100;

    cout << "Uruchamianie aproksymacji sredniokwadratowej wielomianowej..." << endl;
    cout << "Przedzial: [" << a << ", " << b << "], Stopien wielomianu: " << stopien << endl << endl;

    vector<double> coeffs = wykonaj_aproksymacje(funkcja_podstawowa, a, b, stopien, simpsonN);

    if (coeffs.empty()) return;

    cout << fixed << setprecision(10);
    cout << endl << "Wspolczynniki aproksymacji:\n";
    for (int i = 0; i < coeffs.size(); i++)
    {
        cout << "  a[" << i << "] = " << coeffs[i] << endl;
    }

    cout << "\nSprawdzanie wartosci (10 punktow kontrolnych): " << endl;
    cout << string(75, '-') << endl;

    double krok = (b - a) / 10.0;
    for (double x = a; x <= b + 0.0001; x += krok)
    {
        double w_oryginalna = funkcja_podstawowa(x);
        double w_aproksymowana = oblicz_wielomian_aproksymacji(x, coeffs);
        double blad = fabs(w_oryginalna - w_aproksymowana);

        cout << "x: " << setw(12) << setprecision(6) << x
             << " | f(x): " << setw(14) << w_oryginalna
             << " | W(x): " << setw(14) << w_aproksymowana
             << " | Blad: " << scientific << setprecision(4) << blad << fixed << endl;
    }

    cout << string(75, '-') << endl;
    cout << "Generowanie tabeli porownawczej (50 punktow):" << endl;
    cout << "x\t\tf_dokladna\t\tW_aproksymacja" << endl;

    int punkty = 50; 
    double h = (b - a) / punkty;

    for (int i = 0; i <= punkty; i++)
    {
        double x_p = a + i * h;
        cout << setprecision(6) << x_p << "\t\t"
             << setprecision(6) << funkcja_podstawowa(x_p) << "\t\t"
             << setprecision(6) << oblicz_wielomian_aproksymacji(x_p, coeffs) << endl;
    }
}
