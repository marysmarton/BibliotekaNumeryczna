#include "../include/gauss.h" 
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

typedef vector<vector<double>> Matrix;

// Funkcja pomocnicza – widoczna tylko w tym pliku
void drukuj_macierz(const Matrix& A)
{
    for (const auto& row : A)
    {
        for (double val : row)
        {
            cout << setw(10) << fixed << setprecision(2) << val << " ";
        }
        cout << endl;
    }
    cout << "\n---------------------------------------------------------------------------------------\n";
}

// Główna funkcja algorytmu
void eliminacja_gaussa(string nazwa_pliku)
{
    // Otwieranie pliku
    ifstream file(nazwa_pliku);

    // Sprawdza czy plik istnieje
    if (!file.is_open())
    {
        cerr << "Nie udalo sie otworzyc pliku: " << nazwa_pliku << endl;
        return;
    }

    string dane;
    int N;
    file >> dane >> dane >> N; // Wczytywanie rozmiaru macierzy

    vector<double> B(N); // Tworzymy wektor wyrazów wolnych 
    Matrix A(N, vector<double>(N + 1));

    file >> dane; // Pomijamy napisy 

    // Wczytywanie wyrazu B: 
    for (int i = 0; i < N; i++)
    {
        file >> B[i];
    }

    file >> dane; // Pomijanie wyrazu A

    // Wczytywanie calej macierzy A
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file >> A[i][j];
        }
        A[i][N] = B[i]; // Dopisywanie b do macierzy na koncu (macierz rozszerzona)
    }

    cout << endl << "Macierz na poczatku: " << endl;
    drukuj_macierz(A);

    for (int i = 0; i < N; i++)
    {
        int glowny = i;

        for (int k = i + 1; k < N; k++)
        {
            if (abs(A[k][i]) > abs(A[glowny][i]))
            {
                glowny = k;
            }
        }
        
        // Wybor elementu glownego i zamiana wierszy (pivot)
        swap(A[i], A[glowny]);

        if (fabs(A[i][N]) < 1e-9) continue;

        for (int k = i + 1; k < N; k++)
        {
            double f = A[k][i] / A[i][i];
            for (int j = i; j <= N; j++)
            {
                A[k][j] -= f * A[i][j];
            }
        }
    }

    cout << endl << "Macierz po eliminacji: " << endl;
    drukuj_macierz(A);

    // Postepowanie wsteczne
    vector<double> x(N);

    for (int i = N - 1; i >= 0; i--)
    {
        if (abs(A[i][i]) < 1e-12) 
        {
            x[i] = 0; 
            continue;
        }

        double suma = A[i][N];

        for (int j = i + 1; j < N; j++)
        {
            suma -= A[i][j] * x[j];
        }

        x[i] = suma / A[i][i];
    }

    cout << endl << "Rozwiazanie: " << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "X " << i + 1 << " = " << x[i] << endl;
    }
}
