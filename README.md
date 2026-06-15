# Biblioteka Numeryczna

## Autor
Maria Marton

Projekt interaktywnej biblioteki metod numerycznych zrealizowany w języku **C++** w ramach zaliczenia przedmiotu Metody Numeryczne. 

Aplikacja posiada konsolowe, interaktywne menu, które pozwala użytkownikowi na intuicyjny wybór algorytmu matematycznego, wczytanie danych testowych oraz wygenerowanie wyników. Zawiera główny program, w którym użytkownik może wybrać metodę, którą chce zastosować. Do pliku dodano odpowiednio skonfigurowane pliki z kodami oraz pliki nagłówkowe .h; przesłano również pliki tekstowe, które są odczytywane przez część z kodów. 

---

## Zawartość mojej biblioteki numerycznej

Program implementuje szeroki wachlarz zagadnień numerycznych podzielonych na bloki tematyczne:

| Kategoria | Zaimplementowane Metody / Algorytmy |
| :--- | :--- |
| **Analiza danych i Pliki** | Wczytywanie danych z plików tekstowych (`.txt`), parsowanie sekcji danych |
| **Interpolacja i Aproksymacja** | <ul><li>Interpolacja wielomianowa Lagrange'a</li><li>Interpolacja wielomianowa Newtona</li><li>Aproksymacja średniokwadratowa</li></ul> |
| **Algebra Liniowa** | <ul><li>Eliminacja Gaussa (rozwiązywanie układów równań)</li><li>Rozkład LU macierzy</li></ul> |
| **Metody Podziału (Miejsca Zerowe)** | <ul><li>Metoda bisekcji</li><li>Metoda Regula Falsi (fałszywej linii)</li><li>Metoda Newtona (stycznych)</li><li>Metoda siecznych</li></ul> |
| **Całkowanie Numeryczne** | <ul><li>Metoda trapezów</li><li>Metoda Simpsona (parabol)</li><li>Kwadratury Gaussa</li></ul> |
| **Równania Różniczkowe** | <ul><li>Metoda Eulera</li><li>Metoda Heuna</li><li>Metoda punktu środkowego</li><li>Metoda Rungego-Kutty IV rzędu (RK4)</li></ul> |
| **Algorytmy pomocnicze** | Schemat Hornera (szybkie obliczanie wartości wielomianu) |

---

## Struktura mojego projektu

Projekt został ustrukturyzowany z podziałem na moduły, co zapewnia czytelność i separację kodu:

* **`src/`** – Pliki źródłowe (`.cpp`) zawierające właściwe implementacje algorytmów numerycznych.
* **`include/`** – Pliki nagłówkowe (`.h`) z deklaracjami funkcji, strukturami danych i definicjami modułów.
* **`data/`** – Pliki tekstowe wejściowe (np. `dane1.txt`, `Gauss.txt`, `LU.txt`, `interpolacja_n.txt`) zawierające punkty węzłowe, macierze i parametry startowe do obliczeń.
* **`output/`** / **Katalog główny** – Miejsce generowania plików wynikowych (np. plików `.csv` i `.txt` gotowych do importu i wizualizacji w programie Excel).

---

## Instrukcja kompilacji oraz uruchomienia projektu

Projekt można łatwo skompilować w środowisku Linux / GitHub Codespaces za pomocą kompilatora `g++`.

### 1. Kompilacja projektu:
Wpisz w terminalu poniższą komendę, aby skompilować plik główny wraz ze wszystkimi modułami z folderu `src`:
```bash
g++ main.cpp src/*.cpp -Iinclude -o program
```
---

### 2. Uruchomienie projektu
Ostatnim krokiem jest uruchomienie programu za pomocą komendy: 
```bash
./program
```
W tym momencie możesz już korzystac z interaktywnego menu i cieszyć się biblioteką numeryczną!


## Przykłady użycia
Aplikacja po uruchomieniu wyświetla interaktywne menu tekstowe. Użytkownik wybiera żądaną operację poprzez wpisanie odpowiedniego numeru.

### Przykład 1: Interpolacja Lagrange'a (Opcja 1)
Po wybraniu opcji `1`, program automatycznie otwiera plik wejściowy `data/dane1.txt`, wyszukuje odpowiednią sekcję danych pomiarowych (węzłów), wykonuje obliczenia numeryczne, a następnie:
1. Wypisuje tabelę porównawczą wartości oryginalnych i zinterpolowanych w terminalu.
2. Generuje plik wynikowy `wyniki_interpolacji.csv` dedykowany do szybkiej wizualizacji wykresów w programie Excel.


### Przykład 2: Metoda Bisekcji i Regula Falsi (Opcja 12)
Po wybraniu opcji `12`, program przechodzi w tryb interaktywnego pobierania parametrów od użytkownika:
```text
Poczatek przedzialu: 0
Koniec przedzialu: 3
Liczba iteracji: 100
Dokladnosc epsilon: 0.0001

===============================
METODA BISEKCJI
===============================
 Iteracja 1: x = 1.500000
 Iteracja 2: x = 0.750000
 ...
 Osiagnieto wymagana dokladnosc!
```
