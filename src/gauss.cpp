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
// Funkcja pomocnicza sluzaca do wyswietlania macierzy rozszerzonej w czytelnym formacie tabelarycznym
//przyjmuje macierz A w postaci referencji jako argument
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
// Glowna funkcja realizujaca rozwiazywanie ukladu rownan liniowych metoda eliminacji Gaussa z pliku tekstowego
//przyjmuje jako argument nazwe pliku tekstowego
void eliminacja_gaussa(string nazwa_pliku)
{
    // Otwieranie pliku
    // Proba otwarcia pliku wejsciowego z danymi ukladu rownan
    ifstream file(nazwa_pliku);

    // Sprawdza czy plik istnieje
    // Sprawdzenie poprawnosci otwarcia pliku i zabezpieczenie przed bledem sciezki
    if (!file.is_open())
    {
        cerr << "Nie udalo sie otworzyc pliku: " << nazwa_pliku << endl;
        return;
    }

    string dane;
    int N;
    file >> dane >> dane >> N; // Wczytanie etykiet tekstowych oraz wymiaru macierzy (N x N)

    vector<double> B(N); // Tworzymy wektor wyrazów wolnych 
    Matrix A(N, vector<double>(N + 1)); // Tworzenie macierzy rozszerzonej [A | B] o rozmiarze N x (N+1)

    file >> dane; // Pomijamy napisy 

    // Wczytywanie wyrazu B:
    // Wczytywanie wartosci do wektora wyrazow wolnych B
    for (int i = 0; i < N; i++)
    {
        file >> B[i];
    }

    file >> dane; // Pomijanie wyrazu A
    // Pominiecie naglowka sekcji macierzy wspolczynnikow A

    // Wczytywanie calej macierzy A
    // Wczytywanie macierzy kwadratowej A i dopisywanie wektora B jako ostatniej kolumny
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file >> A[i][j];
        }
        A[i][N] = B[i]; // Dopisywanie b do macierzy na koncu (macierz rozszerzona)
        // Konstruowanie pelnej macierzy rozszerzonej ukladu
    }

    cout << endl << "Macierz na poczatku: " << endl;
    drukuj_macierz(A);
    // ETAP 1: Eliminacja w przod (sprowadzanie macierzy do postaci trojkatnej gornej)

    for (int i = 0; i < N; i++)
    {
        int glowny = i;
// Szukanie elementu o najwiekszej wartosci bezwzglednej w biezacej kolumnie (czesciowy wybor elementu osiowego)
        for (int k = i + 1; k < N; k++)
        {
            if (abs(A[k][i]) > abs(A[glowny][i]))
            {
                glowny = k;
            }
        }
        
        // Wybor elementu glownego i zamiana wierszy (pivot)
        // Zamiana biezacego wiersza z wierszem zawierajacym znaleziony element glowny (pivot) w celu poprawy stabilnosci numerycznej
        swap(A[i], A[glowny]);

        // Zabezpieczenie przed dzieleniem przez zero w przypadku ukladow sprzecznych lub nieoznaczonych
        if (fabs(A[i][N]) < 1e-9) continue;

        // Zerowanie elementow ponizej przekatnej w i-tej kolumnie
        for (int k = i + 1; k < N; k++)
        {
            double f = A[k][i] / A[i][i];
            for (int j = i; j <= N; j++)
            {
                A[k][j] -= f * A[i][j];
            }
        }
    }

    // Wyswietlenie koncowego wektora rozwiazan ukladu rownan liniowych
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
// Przypisanie wyrazu wolnego z ostatniej kolumny
        double suma = A[i][N];
// Wyznaczanie sumy znanych juz skladnikow rownania
        for (int j = i + 1; j < N; j++)
        {
            suma -= A[i][j] * x[j];
        }
// Obliczenie ostatecznej wartosci i-tej zmiennej
        x[i] = suma / A[i][i];
    }

    cout << endl << "Rozwiazanie: " << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "X " << i + 1 << " = " << x[i] << endl;
    }
}
