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

    cout << " 1. Interpolacja Lagrange'a" << endl;
    cout << " 2. Interpolacja Newtona" << endl;
    cout << " 3. Schemat Hornera" << endl;
    cout << " 4. Eliminacja Gaussa" << endl;
    cout << " 5. Rozklad LU" << endl;
    cout << " 6. Calkowanie numeryczne" << endl;
    cout << " 7. Aproksymacja sredniokwadratowa" << endl;
    cout << " 8. Metoda Eulera" << endl;
    cout << " 9. Metoda Heuna" << endl;
    cout << "10. Metoda punktu srodkowego" << endl;
    cout << "11. Metoda Rungego-Kutty IV rzedu" << endl;
    cout << "12. Metoda bisekcji i falszywej linii" << endl;
    cout << "13. Metoda Newtona i metoda siecznych" << endl;
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
            interpolacja_lagrange();
            break;
        }

        case 2:
        {
            interpolacja_newtona();
            break;
        }

        case 3:
        {
            metoda_hornera();
            break;
        }

        case 4:
        {
            eliminacja_gaussa("data/Gauss.txt");
            break;
        }

        case 5:
        {
            metoda_LU("data/LU.txt");
            break;
        }

        case 6:
        {
            metoda_calkowania();
            break;
        }

        case 7:
        {
            metoda_aproksymacji();
            break;
        }

        case 8:
        {
            metoda_eulera();
            break;
        }

        case 9:
        {
            metoda_heuna();
            break;
        }

        case 10:
        {
            metoda_punktu_srodkowego();
            break;
        }

        case 11:
        {
            metoda_kutty();
            break;
        }

        case 12:
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
