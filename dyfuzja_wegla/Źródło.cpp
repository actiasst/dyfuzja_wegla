#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

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
	double deltaTemp = 0;

	string nazwa = "";
	fstream plik;
	while (true) {
		cout << "Podaj temperature: ";
		cin >> temp;
		cout << "Podaj nagrzewanie: ";
		cin >> deltaTemp;
		cout << "Podaj krok czasowy: ";
		cin >> t;
		deltaTemp *= t;
		cout << "Podaj nazwe pliku: ";
		cin.ignore();
		getline(cin, nazwa);


		double tab_wynik[ROZMIAR];
		double tab_wynik_tmp[ROZMIAR];
		for (int i = 0; i < ROZMIAR; i++) {
			tab_wynik[i] = 0;
			tab_wynik_tmp[i] = 0;
		}

		for (int i = 0; i < 6; i++) {
			tab_wynik[i] = 0.67;
			tab_wynik_tmp[i] = 0.67;
		}

		for (int i = 6; i < ROZMIAR; i++) {
			tab_wynik[i] = 0.02;
			tab_wynik_tmp[i] = 0.02;
		}

		int obecna_komorka = 6;

		for (int i = 0; i < 200; i++) {
			D = d0 * (exp(-Q / (R * temp_kelwin))) * 1E10;
			temp_kelwin = temp + 273;
			for (int j = 1; j < obecna_komorka; j++)
				tab_wynik_tmp[j] = (1 - 2 * D * t)*tab_wynik[j] + D * t *(tab_wynik[j - 1] + tab_wynik[j + 1]);
			tab_wynik_tmp[0] = (1 - 2 * D * t)*tab_wynik[0] + D * t *(tab_wynik[1] + tab_wynik[1]);
			tab_wynik_tmp[obecna_komorka] = (1 - 2 * D * t)*tab_wynik[obecna_komorka] + D * t *(tab_wynik[obecna_komorka - 1] + tab_wynik[obecna_komorka - 1]);
			for (int j = 0; j <= obecna_komorka; j++)
				tab_wynik[j] = tab_wynik_tmp[j];
			if (!(0 < (-245.5)*tab_wynik[obecna_komorka] + 912 - temp)) {
				obecna_komorka++;
				if (obecna_komorka > ROZMIAR)
					obecna_komorka = ROZMIAR;
			}
			temp += deltaTemp;
		}



		plik.open("C:\\Users\\Lord Actias\\Downloads\\" + nazwa + ".csv", ios::out);
		for (int i = 0; i < ROZMIAR; i++)
			plik << tab_wynik[i] << endl;
		plik.close();
	}

	system("pause");
}