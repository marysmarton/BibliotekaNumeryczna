#include "../include/horner.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

// Metoda tradycyjna
double potegaNaturalna(const vector<double>& a, double x) 
{
    double wynik = 0;
    for (size_t i = 0; i < a.size(); i++) 
    {
        wynik += a[i] * pow(x, i);
    }
    return wynik;
}

// Algorytm Hornera
double horner(const vector<double>& a, double x) 
{
    double wynik = a.back();
    for (int i = (int)a.size() - 2; i >= 0; i--)
    {
        wynik = wynik * x + a[i];
    }
    return wynik;
}

// Główna funkcja wywoływana z poziomu menu
void metoda_hornera() 
{
    ifstream file("data/interpolacja_h.txt"); // ścieżka dostosowana do folderu data/
    if (!file) 
    {
        cerr << "Blad: nie mozna otworzyc pliku data/interpolacja_h.txt" << endl;
        return;
    }

    string line;
    vector<double> a_coeffs, xi_values;
    bool foundSection = false;

    while (getline(file, line))
    {
        if (line.find("l.p.: 5") != string::npos) foundSection = true;
        if (!foundSection) continue;

        if (line.find("a0=") != string::npos) 
        {
            stringstream ss(line);
            string segment;
            while (ss >> segment)
            {
                size_t eqPos = segment.find('=');
                if (eqPos != string::npos) 
                {
                    a_coeffs.push_back(stod(segment.substr(eqPos + 1)));
                }
            }
        }
        else if (line.find("xi:") != string::npos)
        {
            stringstream ss(line.substr(line.find("xi:") + 3));
            double val;
            while (ss >> val) xi_values.push_back(val);
        }
    }
    file.close();

    if (a_coeffs.empty() || xi_values.empty())
    {
        cout << "Blad: Brak danych w sekcji 5 pliku interpolacja_h.txt" << endl;
        return;
    }

    cout << "=========================================================================================" << endl;
    cout << "Porownanie wydajnosci - metoda natyralna vs schemat Hornera" << endl;
    cout << "=========================================================================================" << endl;
    cout << fixed << setprecision(8);
    cout << "n\tLiczba wsp.\tCzas Naturalna [ns]\tCzas Horner [ns]\tWynik (Horner)" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    for (size_t n = 3; n <= a_coeffs.size(); n++) 
    {
        vector<double> sub_a(a_coeffs.begin(), a_coeffs.begin() + n);

        // Pomiar dla metody tradycyjnej
        auto start1 = chrono::high_resolution_clock::now();
        double res1 = 0;
        for (double x : xi_values) res1 = potegaNaturalna(sub_a, x);
        auto end1 = chrono::high_resolution_clock::now();

        // Pomiar dla schematu Hornera
        auto start2 = chrono::high_resolution_clock::now();
        double res2 = 0;
        for (double x : xi_values) res2 = horner(sub_a, x);
        auto end2 = chrono::high_resolution_clock::now();

        auto diff1 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
        auto diff2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();

        cout << n - 1 << "\t" << n << "\t\t" << diff1 << "\t\t\t" << diff2 << "\t\t" << res2 << endl;
    }
}
