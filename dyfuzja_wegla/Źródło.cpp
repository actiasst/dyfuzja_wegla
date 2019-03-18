#include <iostream>
#include <cmath>

using namespace std;

#define ROZMIAR 100

int main() {
	double temp = 780;
	double Q = 140000;
	double R = 8.3144;
	double temp_kelwin = temp + 273;
	double d0 = 0.000041;
	double D = d0 * (exp(-Q / (R * temp_kelwin))) * 1E10;
	double t = 1;

	double tab_wynik[ROZMIAR];
	double tab_wynik_tmp[ROZMIAR];
	for (int i = 0; i < ROZMIAR; i++) {
		tab_wynik[i] = 0;
		tab_wynik_tmp[i] = 0;
	}

	for (int i = 0; i < 6; i++) {
		tab_wynik[i] = 0.65;
		tab_wynik_tmp[i] = 0.65;
	}

	for (int i = 6; i < ROZMIAR; i++) {
		tab_wynik[i] = 0.02;
		tab_wynik_tmp[i] = 0.02;
	}

	int obecna_komorka = 6;

	for (int i = 0; i < 1200; i++) {
		for (int j = 1; j <= obecna_komorka; j++) {
			tab_wynik_tmp[j] = (1 - 2 * D * t)*tab_wynik[j] + D * t *(tab_wynik[j - 1] + tab_wynik[j + 1]);
		}
		for (int j = 1; j <= obecna_komorka; j++)
			tab_wynik[j] = tab_wynik_tmp[j];
		tab_wynik[obecna_komorka+1] = tab_wynik[obecna_komorka];
		//tab_wynik[0] = tab_wynik[1];
		if (!(0 < (-245.5)*tab_wynik[obecna_komorka] + 912 - temp)) {
			tab_wynik[obecna_komorka + 1] = 0.02;
			obecna_komorka++;
		}
	}

	for (int i = 0; i < 20; i++) {
		cout << i << ": " << tab_wynik[i] << endl;
	}


	system("pause");
}