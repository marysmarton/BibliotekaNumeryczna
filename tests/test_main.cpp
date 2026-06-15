#include "../include/horner.h"
#include "../include/newton.h"
#include "../include/calki.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

// Pomocnicza funkcja do testowania metod Newtona 
double f_test(double x) { return x * x - 4.0; }
double df_test(double x) { return 2.0 * x; }

int main()
{
    cout << "Tetsy jednostkowe" << endl;
  //testy metoda hornera 
  //(W(x) = 2x + 3 -> wektor: {3, 2})
    vector<double> wielomian = {3.0, 2.0};
    
    // Test 1: W(0) powinien dac 3
    assert(horner(wielomian, 0.0) == 3.0);
    cout << "[OK] Horner Test 1: W(0) = 3" << endl;

    // Test 2: W(2) powinien dac 2*2 + 3 = 7
    assert(horner(wielomian, 2.0) == 7.0);
    cout << "[OK] Horner Test 2: W(2) = 7" << endl;

//testy dla metody Newtona - szukanie pierwiastka x^2 - 4, powinno wyjsc 2
    double wynik_newton = 0.0;

    // Test 1: Start z x0 = 6.0, powinien znalezc pierwiastek bliski 2.0
    bool sukces1 = metoda_newtona(20, 6.0, wynik_newton, f_test, df_test); 
    assert(sukces1 == true);
    assert(abs(wynik_newton - 2.0) < 1e-5);
    cout << "[OK] Newton Test 1: Znaleziono pierwiastek bliski 2.0" << endl;

    // Test 2: Sprawdzenie ochrony przed dzieleniem przez zero (start w x0 = 0, gdzie pochodna 2x = 0)
    bool sukces2 = metoda_newtona(20, 0.0, wynik_newton, f_test, df_test);
    assert(sukces2 == false); // Powinien zwrocic false z powodu pochodnej rownej 0
    cout << "[OK] Newton Test 2: Poprawne wykrycie dzielenia przez zero" << endl;


 //testy calkowanie - metoda trapezow 
    //dane calki dla wielomianu stopnia 0: W(x) = 5 (ai = {5})
    // Calka z f(x)=5 na przedziale [0, 2] to 5 * (2 - 0) = 10
    dane_calki dane_testowe;
    dane_testowe.n = 0;
    dane_testowe.a = 0.0;
    dane_testowe.b = 2.0;
    dane_testowe.ai = {5.0};

    // Test 1: Calka na przedziale [0, 2] z funkcji stalej 5 na 10 przedzialach
    double wynik_calki = metoda_trapezow_wielomian(0.0, 2.0, 10, dane_testowe);
    assert(abs(wynik_calki - 10.0) < 1e-6);
    cout << "[OK] Calki Test 1: Calka z f(x)=5 na [0,2] wynosi 10" << endl;

    // Test 2: Calka na przedziale [0, 0] (pusty przedzial) powinna dac 0
    double wynik_calki_zero = metoda_trapezow_wielomian(0.0, 0.0, 10, dane_testowe);
    assert(wynik_calki_zero == 0.0);
    cout << "[OK] Calki Test 2: Calka na przedziale zero-jednostkowym wynosi 0" << endl;

  cout<<"tetsy zakonczone powodzeniem"<<endl;

    return 0;
}
