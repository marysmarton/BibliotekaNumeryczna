#include "../include/interpolacja.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

struct InterpPoint
{
    double x, y;
};

// Funkcja pomocnicza wczytująca liczby z pliku
vector<double> extractNumbersInterp(const string& line, const string& prefix)
{
    vector<double> numbers;
    size_t pos = line.find(prefix);
    if (pos == string::npos) return numbers;

    string content = line.substr(pos + prefix.length());
    stringstream ss(content);
    double val;
    while (ss >> val)
    {
        numbers.push_back(val);
    }
    return numbers;
}

// Algorytm wielomianu interpolacyjnego Newtona
double obliczNewtonInterp(const vector<InterpPoint>& nodes, double x)
{
    size_t n = nodes.size();
    if (n == 0) return 0.0;

    vector<vector<double>> d(n, vector<double>(n));
    for (size_t i = 0; i < n; i++)
    {
        d[i][0] = nodes[i].y;
    }

    for (size_t j = 1; j < n; j++)
    {
        for (size_t i = 0; i < n - j; i++)
        {
            d[i][j] = (d[i + 1][j - 1] - d[i][j - 1]) / (nodes[i + j].x - nodes[i].x);
        }
    }

    double wynik = d[0][0];
    double t = 1.0;

    for (size_t i = 1; i < n; i++)
    {
        t *= (x - nodes[i - 1].x);
        wynik += d[0][i] * t;
    }

    return wynik;
}

void zapiszDoExcelaInterp(const vector<InterpPoint>& allPoints, const vector<InterpPoint>& nodes) 
{
    ofstream file("dane_do_excela.txt");
    if (!file.is_open()) return;

    file << "X\tInterpolacja\tWezly" << endl;
    for (const auto& p : allPoints)
    {
        double y_interp = obliczNewtonInterp(nodes, p.x);
        file << p.x << "\t" << y_interp << "\t" << "" << endl;
    }

    for (const auto& n : nodes) 
    {
        file << n.x << "\t" << "" << "\t" << n.y << endl;
    }
    file.close();
}

// Główna funkcja wywoływana z poziomu menu
void metoda_interpolacji()
{
    ifstream file("data/interpolacja_n.txt"); //ścieżka dostosowana do folderu data/
    if (!file)
    {
        cout << "Blad: nie mozna otworzyc pliku data/interpolacja_n.txt" << endl;
        return;
    }

    string line;
    vector<double> x_values, y_values;
    bool foundSection = false;

    while (getline(file, line))
    {
        if (line.find("l.p.: 5") != string::npos || line.find("l.p. 5") != string::npos)
        {
            foundSection = true;
            continue;
        }

        if (foundSection)
        {
            if (line.find("xi:") != string::npos)
            {
                x_values = extractNumbersInterp(line, "xi:");
            }
            else if (line.find("f(xi):") != string::npos)
            {
                y_values = extractNumbersInterp(line, "f(xi):");
                break; 
            }
        }
    }
    file.close();

    vector<InterpPoint> myData;
    size_t dataSize = min(x_values.size(), y_values.size());
    for (size_t i = 0; i < dataSize; i++)
    {
        myData.push_back({ x_values[i], y_values[i] });
    }

    if (myData.empty())
    {
        cout << "BLAD: Nie udalo sie wczytac danych sekcji 5. Sprawdz format pliku." << endl;
        return;
    }

    vector<InterpPoint> nodes;
    for (size_t i = 0; i < myData.size(); i += 5)
    {
        nodes.push_back(myData[i]);
    }

    cout << "=========================================" << endl;
    cout << "INTERPOLACJA NEWTONA (SEKCJA 5)" << endl;
    cout << "=========================================" << endl;
    cout << "Wczytano " << myData.size() << " punktow." << endl;
    cout << "Uzyto " << nodes.size() << " wezlow do interpolacji." << endl;
    cout << "-----------------------------------------" << endl;

    for (size_t i = 0; i < min((size_t)15, myData.size()); i++)
    {
        double x = myData[i].x;
        cout << "x = " << x << "\t Oryginalne y = " << myData[i].y
             << "\t Interpolacja = " << obliczNewtonInterp(nodes, x) << endl;
    }

    zapiszDoExcelaInterp(myData, nodes);
    cout << "\nZapisano zestawienie punktow do pliku 'dane_do_excela.txt'" << endl;
}
