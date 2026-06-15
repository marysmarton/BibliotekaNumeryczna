#include "../include/rk.h" 
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;


double rozwiazanie_dokladne(double t)
{
    double T = 14935000.0 / pow((79951556409.0 * t) / 2.0 + 15625000000.0, 1.0 / 3.0);
    return T;
}


double pochodna(double T)
{
    double dT = 0.0;
    double beta = 0.0;
    double alfa = -4 * pow(10, -12);
    dT = alfa * (pow(T, 4) - beta);
    return dT;
}


void metoda_heuna()
{
    double T0 = 5974.0; 
    double t0 = 0.0; 
    double t_end = 5974.0; 
    int n = 100000; 
    double h = t_end / n; 

    vector<double> t(n + 1);
    vector<double> T(n + 1);

    t[0] = t0;
    T[0] = T0;

    for (int i = 0; i < n; i++)
    {
        t[i + 1] = t[i] + h;
        double T_predyktor = T[i] + h * pochodna(T[i]);
        T[i + 1] = T[i] + (h / 2.0) * (pochodna(T[i]) + pochodna(T_predyktor));
    }

    cout << "t[s]        T_Heun        T_exact\n";
    for (int i = 0; i <= n; i += n / 20)
    {
        cout << fixed << setprecision(6) << setw(8) << t[i] << "   "
             << setw(12) << T[i] << "   "
             << setw(12) << rozwiazanie_dokladne(t[i])
             << "\n";
    }
}


void metoda_punktu_srodkowego()
{
    double T0 = 5974.0; 
    double t0 = 0.0; 
    double t_end = 5974.0; 
    int n = 100000; 
    double h = t_end / n; 

    vector<double> t(n + 1);
    vector<double> T(n + 1);

    T[0] = T0;
    t[0] = t0;

    for (int i = 0; i < n; i++)
    {
        t[i + 1] = t[i] + h;
        double T_polowa = T[i] + 0.5 * h * pochodna(T[i]);
        T[i + 1] = T[i] + h * pochodna(T_polowa);
    }

    cout << "t[s]        T_srodkowy        T_exact\n";
    for (int i = 0; i <= n; i += n / 20)
    {
        cout << fixed << setprecision(6) << setw(8) << t[i] << "   "
             << setw(12) << T[i] << "   "
             << setw(12) << rozwiazanie_dokladne(t[i])
             << "\n";
    }
}


void metoda_kutty()
{
    double T0 = 5974.0; 
    double t0 = 0.0; 
    double t_end = 5974.0; 
    int n = 100000; 
    double h = t_end / n; 

    vector<double> t(n + 1);
    vector<double> T(n + 1);

    T[0] = T0;
    t[0] = t0;

    for (int i = 0; i < n; i++)
    {
        t[i + 1] = t[i] + h;
        double k1, k2, k3, k4;

        k1 = pochodna(T[i]);
        k2 = pochodna(T[i] + 0.5 * h * k1);
        k3 = pochodna(T[i] + 0.5 * h * k2);
        k4 = pochodna(T[i] + h * k3);

        T[i + 1] = T[i] + (h / 6.0) * (k1 + k4 + 2.0 * (k2 + k3));
    }

    cout << "t[s]        T_Kutty        T_exact\n";
    for (int i = 0; i <= n; i += n / 20)
    {
        cout << fixed << setprecision(6) << setw(8) << t[i] << "   "
             << setw(12) << T[i] << "   "
             << setw(12) << rozwiazanie_dokladne(t[i])
             << "\n";
    }
}
