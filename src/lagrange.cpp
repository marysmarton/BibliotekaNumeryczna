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
// Funkcja pomocnicza wyciagajaca liczby z konkretnej linii tekstu na podstawie podanego prefiksu (np. "xi:")
vector<double> extractNumbersLagrange(const string& line, const string& prefix) 
{
    vector<double> numbers;
    size_t pos = line.find(prefix);
    if (pos == string::npos) return numbers; // Jesli nie znaleziono prefiksu, zwraca pusty wektor

    string content = line.substr(pos + prefix.length());
    stringstream ss(content);
    double val;
    while (ss >> val) 
    {
        numbers.push_back(val);
    }
    //funkcja zwraca liczby wczytane z tekstu
    return numbers;
}

// Algorytm obliczajacy wartosc wielomianu interpolacyjnego Lagrange'a w zadanym punkcie x
// Algorytm interpolacji Lagrange'a
//przyjmuje punkty przez ktore musi przejsc wielomian oraz punkt x
double lagrange_wlasciwy(const vector<LagrangePoint>& nodes, double x)
{
    double result = 0.0;
    // Glowna petla sumujaca poszczegolne skladniki wielomianu
    for (size_t i = 0; i < nodes.size(); i++) 
    {
        double term = nodes[i].y; // Startujemy od wartosci y_i dla danego wezla
        for (size_t j = 0; j < nodes.size(); j++) // Petla wyznaczajaca iloczyn wielomianow bazowych Lagrange'a (L_i)
        {
            if (i != j)  // Pomijamy przypadek, gdy indeksy sa równe (unikamy dzielenia przez zero)
            {
                term *= (x - nodes[j].x) / (nodes[i].x - nodes[j].x);
            }
        }
        result += term; // Dodawanie wyznaczonego skladnika do ostatecznego wyniku
    }
    //funkcja zwraca wartosc wielomianu w punkcie z
    return result;
}

// Zapis wyników do pliku CSV (czytelnego dla Excela)
// Funkcja eksportujaca zestawienie danych do pliku CSV z podzialem na sredniki (format czytelny dla Excela)
//przyjmuje nazwe pliku wyjsciowego wszystkie wezly oraz wszystkie punkty
void zapisz_csv(const string& filename, const vector<LagrangePoint>& allData, const vector<LagrangePoint>& nodes) 
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cout << "BLAD: Nie mozna utworzyc pliku " << filename << endl;
        return;
    }
// Zapisywanie naglowka kolumn tabeli
    outFile << "x;y_original;y_interpolated;is_node\n";
// Przechodzenie przez wszystkie punkty pomiarowe i wyznaczanie dla nich wartosci zinterpolowanych
    for (const auto& p : allData) 
    {
        double interpY = lagrange_wlasciwy(nodes, p.x);
// Sprawdzanie, czy dany punkt pomiarowy byl wykorzystany jako wezel interpolacji
        bool isNode = false;
        for (const auto& n : nodes) 
        {
            if (abs(n.x - p.x) < 1e-6) 
            { 
                isNode = true;
                break;
            }
        }
// Zapisywanie gotowej linii danych do pliku tekstowego
        outFile << p.x << ";" << p.y << ";" << interpY << ";" << (isNode ? "TAK" : "NIE") << "\n";
    }

    outFile.close();
    cout << "Pomyslnie zapisano dane do pliku: " << filename << endl;
}

// Glowna funkcja sterujaca modulem interpolacji Lagrange'a, wywolywana z menu glownego (case 1)
// Główna funkcja wywoływana przez menu główne
void interpolacja_lagrange() 
{
    // Otwieranie pliku tekstowego z danymi wezlowymi
    ifstream file("data/dane1.txt"); //ścieżka dostosowana do folderu data/
    if (!file) 
    {
        cout << "BLAD: Nie mozna otworzyc pliku 'data/dane1.txt'!" << endl;
        return;
    }

    string line;
    vector<double> x_values, y_values;
    bool foundSection = false;
// Odczytywanie pliku wejsciowego i poszukiwanie poczatku sekcji pomiarowej numer 5
    while (getline(file, line)) 
    {
        if (line.find("l.p.: 5") != string::npos || line.find("l.p. 5") != string::npos)
        {
            foundSection = true;
            continue;
        }

        if (foundSection) 
        {
            // Wczytywanie wartosci xi oraz f(xi) do odpowiadajacych im tablic dynamicznych
            if (line.find("xi:") != string::npos) 
            {
                x_values = extractNumbersLagrange(line, "xi:");
            }
            else if (line.find("f(xi):") != string::npos)
            {
                y_values = extractNumbersLagrange(line, "f(xi):");
                break; // Po odczytaniu kompletu danych przerywamy czytanie pliku
            }
        }
    }
    file.close();
// Przepisywanie rozproszonych wektorow x i y do jednego wektora struktur LagrangePoint
    vector<LagrangePoint> myData;
    size_t dataSize = min(x_values.size(), y_values.size());
    for (size_t i = 0; i < dataSize; i++)
    {
        myData.push_back({ x_values[i], y_values[i] });
    }
// Walidacja poprawnosci wczytania struktury danych
    if (myData.empty()) 
    {
        cout << "BLAD: Nie udalo sie wczytac danych sekcji 5. Sprawdz format pliku." << endl;
        return;
    }
    vector<LagrangePoint> nodes;
    // Wybieranie co piatego punktu z serii jako oficjalnego wezla interpolacji
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
// Wyswietlanie porownania oryginalnych y z wartosciami wyliczonymi przez algorytm dla pierwszych 15 probek
    for (size_t i = 0; i < min((size_t)15, myData.size()); i++)
    {
        double x = myData[i].x;
        cout << "x = " << setw(8) << x 
             << "\t Oryginalne y = " << setw(12) << myData[i].y
             << "\t Interpolacja = " << setw(12) << lagrange_wlasciwy(nodes, x) << endl;
    }
// Uruchomienie eksportu wynikow do pliku wynikowego CSV
    cout << "------------------------------------------" << endl;
    zapisz_csv("wyniki_interpolacji.csv", myData, nodes);
}
