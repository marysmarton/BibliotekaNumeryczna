#include <iostream>
#include "aproksymacja.h"
#include "bisekcja.h"
#include "calki.h"
#include "euler.h"
#include "gauss.h"
#include "horner.h"
#include "interpolacja.h"
#include "lagrange.h"
#include "lu.h"
#include "newton.h"
#include "pliki.h"
#include "rk.h"

using namespace std;

void wyswietl_menu()
{
    cout << endl;
    cout << "==========================================================" << endl;
    cout << "             BIBLIOTEKA METOD NUMERYCZNYCH" << endl;
    cout << "==========================================================" << endl;
    cout << endl;

    cout << " 1. Wczytywanie danych z plikow" << endl;
    cout << " 2. Interpolacja Lagrange'a" << endl;
    cout << " 3. Interpolacja Newtona" << endl;
    cout << " 4. Schemat Hornera" << endl;
    cout << " 5. Eliminacja Gaussa" << endl;
    cout << " 6. Rozklad LU" << endl;
    cout << " 7. Calkowanie numeryczne" << endl;
    cout << " 8. Aproksymacja sredniokwadratowa" << endl;
    cout << " 9. Metoda Eulera" << endl;
    cout << "10. Metoda Heuna" << endl;
    cout << "11. Metoda punktu srodkowego" << endl;
    cout << "12. Metoda Rungego-Kutty IV rzedu" << endl;
    cout << "13. Metoda bisekcji i falszywej linii" << endl;
    cout << "14. Metoda Newtona i metoda siecznych" << endl;
    cout << endl;
    cout << " 0. Wyjscie z programu" << endl;
    cout << endl;
    cout << "==========================================================" << endl;
}

int main()
{
    int wybor;

    do
    {
        wyswietl_menu();

        cout << endl;
        cout << "Podaj numer wybranej metody: ";
        cin >> wybor;

        cout << endl;

        switch (wybor)
        {

        case 1:
        {
            string nazwa;

            cout << "Podaj nazwe pliku: ";
            cin >> nazwa;

            if (nazwa == "dane_3.txt")
            {
                wczytaj_dane3("data/" + nazwa, "output/wynik_dane3.csv");
            }
            else
            {
                vector<Punkt> dane;

                wczytaj_dane1("data/" + nazwa, dane);

                if (!dane.empty())
                {
                    zapisz_csv("output/wynik.csv", dane);
                }
            }

            break;
        }

        case 2:
        {
            interpolacja_lagrange();
            break;
        }

        case 3:
        {
            interpolacja_newtona();
            break;
        }

        case 4:
        {
            horner_program();
            break;
        }

        case 5:
        {
            eliminacja_gaussa("data/Gauss.txt");
            break;
        }

        case 6:
        {
            metoda_LU("data/LU.txt");
            break;
        }

        case 7:
        {
            metoda_calkowania();
            break;
        }

        case 8:
        {
            metoda_aproksymacji();
            break;
        }

        case 9:
        {
            metoda_eulera();
            break;
        }

        case 10:
        {
            metoda_heuna();
            break;
        }

        case 11:
        {
            metoda_punktu_srodkowego();
            break;
        }

        case 12:
        {
            metoda_kutty();
            break;
        }

        case 13:
        {
            double a, b, eps;
            int n;

            cout << "Poczatek przedzialu: ";
            cin >> a;

            cout << "Koniec przedzialu: ";
            cin >> b;

            cout << "Liczba iteracji: ";
            cin >> n;

            cout << "Dokladnosc epsilon: ";
            cin >> eps;

            cout << endl;

            cout << "===============================" << endl;
            cout << "METODA BISEKCJI" << endl;
            cout << "===============================" << endl;

            bisekcja(n, a, b, eps);

            cout << endl;

            cout << "===============================" << endl;
            cout << "METODA FALSZYWEJ LINII" << endl;
            cout << "===============================" << endl;

            false_line(n, a, b, eps);

            break;
        }

        case 14:
        {
            double x0;
            int n;

            cout << "Podaj punkt startowy: ";
            cin >> x0;

            cout << "Podaj liczbe iteracji: ";
            cin >> n;

            uruchom_metody_newtona_i_siecznych(x0, n);

            break;
        }

        case 0:
        {
            cout << endl;
            cout << "Dziekujemy za skorzystanie z biblioteki." << endl;
            break;
        }

        default:
        {
            cout << endl;
            cout << "Niepoprawny wybor." << endl;
            break;
        }

        }

        if (wybor != 0)
        {
            cout << endl;
            cout << "------------------------------------------" << endl;
            cout << "Nacisnij ENTER aby wrocic do menu...";
            cin.ignore();
            cin.get();
        }

    } while (wybor != 0);

    return 0;
}
