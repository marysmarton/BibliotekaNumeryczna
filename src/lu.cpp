#include "../include/lu.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

typedef vector<vector<double>> Matrix;

// Funkcja pomocnicza do wyświetlania macierzy
void drukuj_macierz_lu(const Matrix& A) 
{
    for (const auto& row : A) 
    {
        for (double val : row) 
        {
            cout << setw(10) << fixed << setprecision(2) << val << " ";
        }
        cout << endl;
    }
}

// Główna funkcja algorytmu rozkładu LU
void metoda_LU(string nazwa_pliku)
{
    ifstream file(nazwa_pliku);
    if (!file.is_open())
    {
        cerr << "Nie udalo sie otworzyc pliku: " << nazwa_pliku << endl;
        return;
    }

    string dane;
    int N;
    // Pominiecie zbędnych opisów i wczytanie N
    file >> dane >> dane >> dane >> dane >> N;

    vector<double> b(N);
    Matrix A(N, vector<double>(N));

    file >> dane;
    for (int i = 0; i < N; i++)
    {
        file >> b[i]; // Wczytywanie wektora b
    }

    file >> dane;
    // Wczytywanie macierzy A
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file >> A[i][j];
        }
    }

    cout << "Macierz A: " << endl;
    drukuj_macierz_lu(A);
    cout << endl;
    cout << "wektor b: " << endl;

    for (int i = 0; i < N; i++)
    {
        cout << b[i] << " ";
    }
    cout << endl << endl;

    // Inicjalizacja macierzy - rozmiar N, wypełnione zerami 
    Matrix L(N, vector<double>(N, 0.0));
    Matrix U(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; i++)
    {
        for (int k = i; k < N; k++)
        {
            double suma = 0;
            for (int j = 0; j < i; j++)
            {
                suma += (L[i][j] * U[j][k]);
            }
            U[i][k] = A[i][k] - suma;
        }

        // Obliczanie macierzy trojkątnej L
        for (int k = i; k < N; k++)
        {
            if (i == k)
            {
                L[i][i] = 1.0; // Na przekątnej znajdują się jedynki
            }
            else
            {
                double suma = 0;
                for (int j = 0; j < i; j++)
                {
                    suma += (L[k][j] * U[j][i]);
                }
                if (U[i][i] == 0)
                {
                    cerr << "Problem - zero znajduje sie na przekatnej macierzy" << endl;
                    return;
                }
                L[k][i] = (A[k][i] - suma) / U[i][i];
            }
        }
    }

    cout << endl;
    cout << "Macierz L:" << endl;
    drukuj_macierz_lu(L);
    cout << endl;
    cout << "Macierz U:" << endl;
    drukuj_macierz_lu(U);

    cout << endl << "rozwiazywanie ukladu rownan - metoda eliminacji Gaussa: " << endl;

    // Uklad: Lz = b
    // 1. Rozwiązywanie Lz = b (Podstawianie w przód)
    vector<double> z(N);
    for (int i = 0; i < N; i++) {
        double suma = 0;
        for (int j = 0; j < i; j++) {
            suma += L[i][j] * z[j];
        }
        z[i] = (b[i] - suma) / L[i][i];
    }

    // 2. Rozwiązywanie Ux = z (Podstawianie w tył)
    vector<double> x(N);
    for (int i = N - 1; i >= 0; i--) {
        double suma = 0;
        for (int j = i + 1; j < N; j++) {
            suma += U[i][j] * x[j];
        }
        x[i] = (z[i] - suma) / U[i][i];
    }

    cout << endl << endl;
    cout << "Rozwiazanie z: " << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "z" << i + 1 << ": " << z[i] << " ";
    }

    cout << endl << endl;

    cout << "Rozwiazanie x: " << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "x" << i + 1 << ": " << x[i] << " ";
    }
        
    Matrix C(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            for (int k = 0; k < N; k++) 
            {
                C[i][j] += L[i][k] * U[k][j];
            }
        }
    }
    cout << endl << endl;
    cout << "Sprawdzenie: " << endl;
    drukuj_macierz_lu(C);
}
