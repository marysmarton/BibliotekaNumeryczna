#include "../include/pliki.h"
#include <iostream>
#include <fstream>

using namespace std;

void wyczysc_pliki_wyjsciowe() {

    ofstream f1("wyniki_interpolacji.csv", ios::trunc);
    ofstream f2("dane_do_excela.txt", ios::trunc);
    f1.close();
    f2.close();
}

bool sprawdz_czy_pliki_istnieja() {
    ifstream f("data/dane1.txt");
    return f.good();
}
