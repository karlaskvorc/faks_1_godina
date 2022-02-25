#include <iostream>
#include <string>

struct vozlisce {
	int key = NULL;
	vozlisce *oce = NULL;
	vozlisce *leviSin = NULL;
	vozlisce *desniSin = NULL;
};


char menu() {							//funkcija za meni in odabir akcije
	std::cout << "=====================================" << std::endl;
	std::cout << "Binarno iskalno drevo - izbira" << std::endl << std::endl;;
	std::cout << "1) Vnos podataka" << std::endl;
	std::cout << "2) Urejen izpis vrednosti" << std::endl;
	std::cout << "3) Izpis povezav" << std::endl;
	std::cout << "4) Iskanje" << std::endl;
	std::cout << "5) Poisci minimum in maksimum" << std::endl;
	std::cout << "6) Poisci predhodnika in naslednika" << std::endl;
	std::cout << "7) Brisi vrednost" << std::endl;
	std::cout << "8) Konec" << std::endl;

	std::string selection;
	do
		if (!getline(std::cin, selection)) {
			exit(EXIT_FAILURE);
		} while (selection.length() == 0);
		return selection[0];
}



void vstavi(vozlisce *&koren, int k) {

	vozlisce *y = NULL;
	vozlisce *x = koren;

	while (x != NULL) {
		y = x;
		if (k < x->key) x = x->leviSin;
		else if (k > x->key) x = x->desniSin;
		else {
			std::cout << "NAPAKA" << std::endl;
			return;
		}
	}

	vozlisce *z = new vozlisce();					//1. DEL
	z->key = k;
	z->oce = y;

	if (y == NULL) koren = z;
	else {
		if (z->key < y->key) y->leviSin = z;
		else  y->desniSin = z;
	}
}


void urejen_izpis(vozlisce *&x) {					//2. DEL
	if (x != NULL) {
		urejen_izpis(x->leviSin);
		std::cout << x->key << " ";
		urejen_izpis(x->desniSin);
	}
}

void izpis_povezav(vozlisce *&x) {					//3. DEL
	if (x->leviSin != NULL) {
		std::cout << x->key << " -> " << x->leviSin->key << std::endl;
		izpis_povezav(x->leviSin);
	}
	if (x->desniSin != NULL) {
		std::cout << x->key << " -> " << x->desniSin->key << std::endl;
		izpis_povezav(x->desniSin);
	}
}

vozlisce *poisci(vozlisce *&T, int k) {				//4. DEL 
	vozlisce *x = T;
	while (x != NULL) {
		if (k == x->key) return x;
		if (k < x->key) x = x->leviSin;
		else x = x->desniSin;
	}
	return x;
}

vozlisce *minimum(vozlisce *&T) {					//5. DEL
	vozlisce *x = T;
	while (x->leviSin != NULL) {
		x = x->leviSin;
	}
	return x;
}
vozlisce *maksimum(vozlisce *&T) {
	vozlisce *x = T;
	while (x->desniSin != NULL) {
		x = x->desniSin;
	}
	return x;
}


vozlisce *naslednik(int nmb, vozlisce *&koren) {	//6. DEL
	vozlisce *x = poisci(koren, nmb);
	if (x->desniSin != NULL) return minimum(x->desniSin);

	vozlisce *y = x->oce;
	while (y != NULL && x == y->desniSin) {
		x = y;
		y = y->oce;
	}
	return y;
}
vozlisce *predhodnik(int nmb, vozlisce *&koren) {
	vozlisce *x = poisci(koren, nmb);
	if (x->leviSin != NULL) return maksimum(x->leviSin);

	vozlisce *y = x->oce;
	while (y != NULL && x == y->leviSin) {
		x = y;
		y = y->oce;
	}
	return y;
}


void brisi(vozlisce *&T, int number) {				//7. DEL
	vozlisce *z = poisci(T, number);
	if (z == NULL) {
		std::cout << "Napaka." << std::endl;
		return;
	}
	vozlisce *y = NULL;
	vozlisce *x = NULL;
	if (z->leviSin == NULL || z->desniSin == NULL) y = z;
	else y = naslednik(z->key, T);

	if (y->leviSin != NULL) x = y->leviSin;
	else x = y->desniSin;

	if (x != NULL) x->oce = y->oce;
	if (y->oce == NULL) T = x;
	else {
		if (y == y->oce->leviSin) y->oce->leviSin = x;
		else y->oce->desniSin = x;
	}

	if (y != z) z->key = y->key;

	delete y;
}


void brisanje(vozlisce *&k) {
	vozlisce *x = k;
	if (x != NULL) {
		brisanje(x->leviSin);
		brisanje(x->desniSin);
		delete x;
	}
}


int main() {
	bool running = true;
	char menu_value;
	int number;
	int d = 0;

	vozlisce *koren = NULL;

	do {
		menu_value = menu();
		switch (menu_value) {

		case '1': {
			std::cout << "Stevilo za vnos:\t";
			std::cin >> number;
			d++;
			vstavi(koren, number);
			break;
		}
		case '2': {
			if (koren == NULL) {
				std::cout << "Napaka!" << std::endl;
				break;
			}
			urejen_izpis(koren);
			std::cout << std::endl;
			break;
		}
		case '3': {
			if (koren == NULL) {
				std::cout << "Napaka!" << std::endl;
				break;
			}
			izpis_povezav(koren);
			std::cout << std::endl;
			break;
		}
		case '4': {
			if (koren == NULL) {
				std::cout << "Napaka!" << std::endl;
				break;
			}
			std::cout << "Trazeno stevilo:\t";
			std::cin >> number;
			vozlisce *stevilo = poisci(koren, number);
			if (stevilo == NULL) std::cout << "Stevilo ne obstaja!" << std::endl;
			else std::cout << "Stevilo obstaja!" << std::endl;
			break;
		}
		case '5': {
			if (koren == NULL) {
				std::cout << "Napaka!" << std::endl;
				break;
			}
			std::cout << "Min element v drevesu: " << minimum(koren)->key << std::endl;
			std::cout << "Max element v drevesu: " << maksimum(koren)->key << std::endl;
			break;
		}
		case '6': {
			std::cout << "Zeleno stevilo:\t";
			std::cin >> number;
			if (koren == NULL) {
				std::cout << "Napaka!" << std::endl;
				break;
			}
			vozlisce *nas = naslednik(number, koren);
			vozlisce *prev = predhodnik(number, koren);
			if (nas == NULL) {
				std::cout << "Naslednik:\tx" << std::endl;
				std::cout << "Predhodnik:\t" << prev->key << std::endl;
				std::cout << "Stevilo je najvekse." << std::endl;
			}
			else if (prev == NULL) {
				std::cout << "Naslednik:\t" << nas->key << std::endl;
				std::cout << "Predhodnik:\tx" << std::endl;
				std::cout << "Stevilo je najmanjse." << std::endl;
			}
			else {
				std::cout << "Naslednik:\t" << nas->key << std::endl;
				std::cout << "Predhodnik:\t" << prev->key << std::endl;
			}
			break;
		}
		case '7': {
			if (koren == NULL) {
				std::cout << "Napaka!" << std::endl;
				break;
			}
			std::cout << "Brisanje:\t";
			std::cin >> number;
			brisi(koren, number);
			break;
		}
		case '8': {
			running = false;
			break;
		}
		default: {
			std::cout << "Napaka pri izbiri. Poskusite se enkrat." << std::endl;
		}
		}
	} while (running);


	brisanje(koren);

	system("pause");
	return 0;
}