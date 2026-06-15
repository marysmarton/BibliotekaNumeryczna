#include "../include/interpolacja.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

//struktura pijedynczego punktu na dwuwymiarowej plaszczyznie zawierajaca jego wspolrzedne x i y
struct InterpPoint
{
    double x, y;
};

// Funkcja pomocnicza wczytująca liczby z pliku
// Funkcja pomocnicza wyciagajaca liczby z konkretnej linii tekstu na podstawie podanego prefiksu (np. "xi:")
//przyjmuje parametr line - biexzaca linia tekstu oraz prefix - ciag znakow ktorych szuka program, aby wiedziec, gdzie zaczac czytac liczby
vector<double> extractNumbersInterp(const string& line, const string& prefix)
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
    //funkcja zwraca liczby wczytane z pliku
    return numbers;
}

// Algorytm wielomianu interpolacyjnego Newtona
// Algorytm wyznaczajacy wartosc wielomianu interpolacyjnego Newtona w zadanym punkcie x
//przyjmuje argumenty nodes - tablica zadanych wezlow interpolacyjnych, przez ktore wielomian musi przejsc oraz x - wzadany punkt x wktorym sie oblicza wartosc wielomianu
double obliczNewtonInterp(const vector<InterpPoint>& nodes, double x)
{
    size_t n = nodes.size();
    if (n == 0) return 0.0;
// Tworzenie dwuwymiarowej tabeli na ilorazy roznicowe
    vector<vector<double>> d(n, vector<double>(n));
    // Pierwsza kolumna tabeli to po prostu wartosci y (f(xi)) naszych wezlow
    for (size_t i = 0; i < n; i++)
    {
        d[i][0] = nodes[i].y;
    }

    // Obliczanie kolejnych rzedow ilorazow roznicowych (kolumna po kolumnie)
    for (size_t j = 1; j < n; j++)
    {
        for (size_t i = 0; i < n - j; i++)
        {
            d[i][j] = (d[i + 1][j - 1] - d[i][j - 1]) / (nodes[i + j].x - nodes[i].x);
        }
    }

    // Schemat Hornera do obliczenia ostatecznej wartosci wielomianu w punkcie x
    double wynik = d[0][0]; // Pierwszy wyraz (a0)
    double t = 1.0;

    for (size_t i = 1; i < n; i++)
    {
        t *= (x - nodes[i - 1].x); // Mnozenie przez kolejne czynniki (x - x_i)
        wynik += d[0][i] * t; // Dodawanie kolejnych skladnikow wielomianu
    }
//funkcja zwraca wartosc wielomianu interpolacyjnego newtona w punkcie x
    return wynik;
}

// Funkcja eksportujaca oryginalne punkty oraz wezly do pliku tekstowego w celu łatwego przeniesienia do Excela
void zapiszDoExcelaInterp(const vector<InterpPoint>& allPoints, const vector<InterpPoint>& nodes) 
{
    ofstream file("dane_do_excela.txt");
    if (!file.is_open()) return;

    file << "X\tInterpolacja\tWezly" << endl;
    // Zapisywanie wartosci zinterpolowanych dla wszystkich dostepnych punktow
    for (const auto& p : allPoints)
    {
        double y_interp = obliczNewtonInterp(nodes, p.x);
        file << p.x << "\t" << y_interp << "\t" << "" << endl;
    }
// Dopisywanie na koncu samych wezlow bazowych, zeby na wykresie Excela wyswietlily sie jako osobna seria
    for (const auto& n : nodes) 
    {
        file << n.x << "\t" << "" << "\t" << n.y << endl;
    }
    file.close();
}

// Główna funkcja wywoływana z poziomu menu
// Glowna funkcja sterujaca modulem interpolacji Newtona, wywolywana z menu glownego (case 2)
void interpolacja_newtona()
{
    // Otwieranie pliku z danymi pomiarowymi
    ifstream file("data/interpolacja_n.txt"); //ścieżka dostosowana do folderu data/
    if (!file)
    {
        cout << "Blad: nie mozna otworzyc pliku data/interpolacja_n.txt" << endl;
        return;
    }

    string line;
    vector<double> x_values, y_values;
    bool foundSection = false;
// Przeszukiwanie pliku linia po linii w celu znalezienia sekcji pomiarowej numer 5
    while (getline(file, line))
    {
        if (line.find("l.p.: 5") != string::npos || line.find("l.p. 5") != string::npos)
        {
            foundSection = true; // Znaleziono poczatek sekcji 5
            continue;
        }

        if (foundSection)// Wczytywanie wartosci xi oraz f(xi) dla znalezionej sekcji
        {
            if (line.find("xi:") != string::npos)
            {
                x_values = extractNumbersInterp(line, "xi:");
            }
            else if (line.find("f(xi):") != string::npos)
            {
                y_values = extractNumbersInterp(line, "f(xi):");
                break; // Po wczytaniu f(xi) mamy komplet danych, konczymy czytanie pliku
            }
        }
    }
    file.close();
// Laczenie rozproszonych wektorow x i y w jedna strukture punktow pomiarowych myData
    vector<InterpPoint> myData;
    size_t dataSize = min(x_values.size(), y_values.size());
    for (size_t i = 0; i < dataSize; i++)
    {
        myData.push_back({ x_values[i], y_values[i] });
    }
// Zabezpieczenie na wypadek braku danych w pliku lub zlego formatowania sekcji
    if (myData.empty())
    {
        cout << "BLAD: Nie udalo sie wczytac danych sekcji 5. Sprawdz format pliku." << endl;
        return;
    }
// Wybieranie co piatego punktu jako wezla interpolacyjnego (redukcja stopnia wielomianu)
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
// Wyswietlanie w konsoli porownania wartosci oryginalnych z wyliczonymi przez wielomian dla pierwszych 15 punktow
    for (size_t i = 0; i < min((size_t)15, myData.size()); i++)
    {
        double x = myData[i].x;
        cout << "x = " << x << "\t Oryginalne y = " << myData[i].y
             << "\t Interpolacja = " << obliczNewtonInterp(nodes, x) << endl;
    }
// Zapis kompletnych wynikow do pliku zewnętrznego
    zapiszDoExcelaInterp(myData, nodes);
    cout << "\nZapisano zestawienie punktow do pliku 'dane_do_excela.txt'" << endl;
}
