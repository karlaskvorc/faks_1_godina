#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <time.h>
#include <cstdlib>
#include <chrono>

char menu() {							//funkcija za meni in odabir akcije
	std::cout << "=====================================" << std::endl;
	std::cout << "Hitro uredi - izbira" << std::endl << std::endl;;
	std::cout << "1) Generiraj nakljucno zaproedje" << std::endl;
	std::cout << "2) Generiraj narascajoce zaporedje" << std::endl;
	std::cout << "3) Generiraj padajoce zaporedje" << std::endl;
	std::cout << "4) Izpis zaporedja" << std::endl;
	std::cout << "5) Preveri ali je zaporedje urejeno" << std::endl;
	std::cout << "6) Uredi s hitrim urejanjem brez mediane" << std::endl;
	std::cout << "7) Uredi s hitrim urejanjem s mediano" << std::endl;
	std::cout << "8) Uredi z seleciton sortom" << std::endl;
	std::cout << "9) Konec" << std::endl;

	std::string selection;
	do
		if (!getline(std::cin, selection)) {
			exit(EXIT_FAILURE);
		} while (selection.length() == 0);
		return selection[0];
}
void izpis_zaporedja(int a[], int vrh) {
	for (int i = 0; i < vrh; i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

void nakljucno_zaporedje(int a[], int vrh) {
	std::mt19937 rndg;
	std::uniform_int_distribution<uint32_t> uint_dist(1, 1000000);
	for (int i = 0; i < vrh; i++) {
		a[i] = uint_dist(rndg);
	}
	//izpis_zaporedja(a, vrh);

}

void nakljucno_zaporedje_narascajoce(int a[], int vrh) {
	int min = 1;
	std::mt19937 rndg;
	for (int i = 0; i < vrh; i++) {
		std::uniform_int_distribution<uint32_t> uint_dist(min, 1000000);
		a[i] = uint_dist(rndg);
		min = a[i];
	}
	//izpis_zaporedja(a, vrh);
}

void nakljucno_zaporedje_padajoce(int a[], int vrh) {
	int max = 1000000;
	std::mt19937 rndg;
	for (int i = 0; i < vrh; i++) {
		std::uniform_int_distribution<uint32_t> uint_dist(1, max);
		a[i] = uint_dist(rndg);
		max = a[i];
	}
	//izpis_zaporedja(a, vrh);
}

int deli(int a[], int dno, int vrh) {
	int pivot = a[dno];
	int levi = dno;
	int desni = vrh;
	do {
		while (a[levi] <= pivot && levi < vrh) levi = levi + 1;
		while (a[desni] >= pivot && desni > dno) desni = desni - 1;
		if (levi < desni) std::swap(a[desni], a[levi]);
	} while (levi < desni);
	std::swap(a[dno], a[desni]);
	return desni;
}

int deli_mediana(int a[], int dno, int vrh) {
	int m = dno + (vrh - dno) / 2;
	int pivot = a[m];
	std::swap(a[dno], a[m]);
	int levi = dno;
	int desni = vrh;
	do {
		while (a[levi] <= pivot && levi < vrh) levi = levi + 1;
		while (a[desni] >= pivot && desni > dno) desni = desni - 1;
		if (levi < desni) std::swap(a[desni], a[levi]);
	} while (levi < desni);
	std::swap(a[dno], a[desni]);
	return desni;
}

void hitro_urejanje_mediana(int a[], int dno, int vrh) {
	int j;
	if (dno < vrh) {
		j = deli_mediana(a, dno, vrh);
		hitro_urejanje_mediana(a, dno, j - 1);
		hitro_urejanje_mediana(a, j + 1, vrh);
	}
}

void hitro_urejanje(int a[], int dno, int vrh) {
	int j;
	if (dno < vrh) {
		j = deli(a, dno, vrh);
		hitro_urejanje(a, dno, j - 1);
		hitro_urejanje(a, j + 1, vrh);
	}
}


bool preveri(int a[], int vrh) {
	for (int i = 0; i < vrh - 1; i++) {
		if (a[i + 1] < a[i]) return false;
	}
	return true;
}

void selection_sort(int a[], int vrh) {
	for (int i = 0; i < vrh - 1; i++) {
		int minInd = i;
		for (int j = i + 1; j < vrh; j++) {
			if (a[j] < a[minInd]) minInd = j;
		}
		if (minInd != i) std::swap(a[i], a[minInd]);
	}
}


int main() {
	srand(time(NULL));
	bool running = true;
	char menu_value;
	int number;

	int vrh = 0;
	int dno = 0;
	int *a = new int[1];

	do {
		menu_value = menu();
		switch (menu_value) {
		case '1': {
			std::cout << "Dimenzije polje:\t" << std::endl;
			std::cin >> vrh;
			delete[] a;
			a = new int[vrh];
			nakljucno_zaporedje(a, vrh);

			break;
		}
		case '2': {
			std::cout << "Dimenzije polje:\t" << std::endl;
			std::cin >> vrh;
			a = new int[vrh];
			nakljucno_zaporedje_narascajoce(a, vrh);
			break;
		}
		case '3': {
			std::cout << "Dimenzije polje:\t" << std::endl;
			std::cin >> vrh;
			a = new int[vrh];
			nakljucno_zaporedje_padajoce(a, vrh);
			break;
		}
		case '4': {
			izpis_zaporedja(a, vrh);
			break;
		}
		case '5': {
			if (preveri(a, vrh)) std::cout << "Zaporedje urejeno." << std::endl;
			else std::cout << "Napacno urejeno polje." << std::endl;
			break;
		}
		case '6': {
			auto start = std::chrono::steady_clock::now();

			hitro_urejanje(a, 0, vrh - 1);
			std::cout << "Uredil sem!" << std::endl;

			auto end = std::chrono::steady_clock::now();
			std::cout << "Cas trajanja : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekundi." << std::endl;
			break;
		}
		case '7': {
			auto start = std::chrono::steady_clock::now();

			hitro_urejanje_mediana(a, 0, vrh - 1);
			std::cout << "Uredil sem!" << std::endl;

			auto end = std::chrono::steady_clock::now();
			std::cout << "Cas trajanja : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekundi." << std::endl;
			break;
		}
		case '8': {
			auto start = std::chrono::steady_clock::now();

			selection_sort(a, vrh);
			std::cout << "Uredil sem!" << std::endl;

			auto end = std::chrono::steady_clock::now();
			std::cout << "Cas trajanja : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekundi." << std::endl;
			break;
		}
		case '9': {
			running = false;
			break;
		}
		default: {
			std::cout << "Wrong selection." << std::endl;
			break;
		}

		}

	} while (running);

	delete[] a;
	system("pause");
	return 0;
}