#include "../include/lagrange.h" 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct LagrangePoint 
{
    double x, y;
};

// Funkcja pomocnicza wczytująca liczby z linii tekstu
vector<double> extractNumbersLagrange(const string& line, const string& prefix) 
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

// Algorytm interpolacji Lagrange'a
double lagrange_wlasciwy(const vector<LagrangePoint>& nodes, double x)
{
    double result = 0.0;
    for (size_t i = 0; i < nodes.size(); i++) 
    {
        double term = nodes[i].y;
        for (size_t j = 0; j < nodes.size(); j++) 
        {
            if (i != j) 
            {
                term *= (x - nodes[j].x) / (nodes[i].x - nodes[j].x);
            }
        }
        result += term;
    }
    return result;
}

// Zapis wyników do pliku CSV (czytelnego dla Excela)
void zapisz_csv(const string& filename, const vector<LagrangePoint>& allData, const vector<LagrangePoint>& nodes) 
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cout << "BLAD: Nie mozna utworzyc pliku " << filename << endl;
        return;
    }

    outFile << "x;y_original;y_interpolated;is_node\n";

    for (const auto& p : allData) 
    {
        double interpY = lagrange_wlasciwy(nodes, p.x);

        bool isNode = false;
        for (const auto& n : nodes) 
        {
            if (abs(n.x - p.x) < 1e-6) 
            { 
                isNode = true;
                break;
            }
        }

        outFile << p.x << ";" << p.y << ";" << interpY << ";" << (isNode ? "TAK" : "NIE") << "\n";
    }

    outFile.close();
    cout << "Pomyslnie zapisano dane do pliku: " << filename << endl;
}

// Główna funkcja wywoływana przez menu główne
void interpolacja_lagrange() 
{
    ifstream file("data/dane1.txt"); //ścieżka dostosowana do folderu data/
    if (!file) 
    {
        cout << "BLAD: Nie mozna otworzyc pliku 'data/dane1.txt'!" << endl;
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
                x_values = extractNumbersLagrange(line, "xi:");
            }
            else if (line.find("f(xi):") != string::npos)
            {
                y_values = extractNumbersLagrange(line, "f(xi):");
                break; 
            }
        }
    }
    file.close();

    vector<LagrangePoint> myData;
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

    vector<LagrangePoint> nodes;
    for (size_t i = 0; i < myData.size(); i += 5) 
    {
        nodes.push_back(myData[i]);
    }

    cout << "=========================================" << endl;
    cout << "INTERPOLACJA LAGRANGE'A (SEKCJA 5)" << endl;
    cout << "=========================================" << endl;
    cout << "Wczytano " << myData.size() << " punktow." << endl;
    cout << "Uzyto " << nodes.size() << " wezlow do interpolacji." << endl;
    cout << "------------------------------------------" << endl;

    for (size_t i = 0; i < min((size_t)15, myData.size()); i++)
    {
        double x = myData[i].x;
        cout << "x = " << setw(8) << x 
             << "\t Oryginalne y = " << setw(12) << myData[i].y
             << "\t Interpolacja = " << setw(12) << lagrange_wlasciwy(nodes, x) << endl;
    }

    cout << "------------------------------------------" << endl;
    zapisz_csv("wyniki_interpolacji.csv", myData, nodes);
}
