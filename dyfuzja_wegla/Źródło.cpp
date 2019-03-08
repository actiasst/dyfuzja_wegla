#include <iostream>
#include <cmath>

using namespace std;

#define ROZMIAR 102

int main() {
	double temp = 727;
	double Q = 140000;
	double R = 8.3144;
	double temp_kelwin = temp + 273;
	double d0 = 0.000041;
	double D = d0 * (exp(-Q / (R * temp_kelwin))) * 1E10;
	double t = 0;

	double tab_wynik[ROZMIAR];
	double tab_wynik_tmp[ROZMIAR];
	for (int i = 0; i < ROZMIAR; i++) {
		tab_wynik[i] = 0;
		tab_wynik_tmp[i] = 0;
	}
	tab_wynik[0] = 0.65;

	for (int j = 0; j < 101; j++) {
		for (int i = 1; i < ROZMIAR - 1; i++) {
			tab_wynik_tmp[i] = (1 - 2 * ((D*t) / (i*i)))*tab_wynik[i] + ((D*t) / (i*i))*(tab_wynik[i - 1] + tab_wynik[i + 1]);
		}
		t++;
		for (int i = 1; i < ROZMIAR - 1; i++)
			tab_wynik[i] = tab_wynik_tmp[i];
	}

	for (int i = 1; i < ROZMIAR - 1; i++)
		cout << i << ": " << tab_wynik_tmp[i] << endl;

	system("pause");
}