#include <iostream>
#include <string>
#include <chrono>

struct seznam {							//konstruiram seznam
	int key = NULL;
	seznam *prev = NULL, *next = NULL;
};

char menu() {							//funkcija za meni in odabir akcije
	std::cout << "=====================================" << std::endl;
	std::cout << "Dvojno povezan seznam - izbira" << std::endl << std::endl;;
	std::cout << "1) Iskanje podataka" << std::endl;
	std::cout << "2) Vnos podatka v glavo" << std::endl;
	std::cout << "3) Vnos podatka za elementom" << std::endl;
	std::cout << "4) Vnos podataka za repom" << std::endl;
	std::cout << "5) Brisanje podataka" << std::endl;
	std::cout << "6) Ispis seznama od glave proti repu" << std::endl;
	std::cout << "7) Ispis seznama od repa proti glavi" << std::endl;
	std::cout << "8) Testiraj hitrost" << std::endl;
	std::cout << "9) Konec" << std::endl;

	std::string selection;
	do
		if (!getline(std::cin, selection)) {
			exit(EXIT_FAILURE);
		} while (selection.length() == 0);
		return selection[0];
}

seznam *najdi(seznam *&head, int stevilo) {
	seznam *temp = head;
	while (temp != NULL && temp->key != stevilo) {
		temp = temp->next;
	}
	return temp;
}

void vstavi_v_glavo(seznam *&head, seznam *&tail, int stevilo) {
	seznam *temp = new seznam;
	temp->key = stevilo;
	temp->next = head;
	temp->prev = NULL;
	if (head != NULL) head->prev = temp;
	else tail = temp;
	head = temp;
}

void vstavi_za_repom(seznam *&head, seznam *&tail, int stevilo) {
	seznam *temp = tail;
	if (temp == NULL) {
		temp = new seznam;
		temp->key = stevilo;
		temp->prev = NULL;
		temp->next = NULL;
		head = temp;
		tail = temp;
		return;
	}
	while (temp != NULL) {
		temp = temp->next;
	}
	temp = new seznam;
	tail->next = temp;
	temp->key = stevilo;
	temp->next = NULL;
	temp->prev = tail;
	tail = temp;
	return;
}

void vstavi_za_elementom(seznam *&head, seznam *&tail, int stevilo, int steviloZa) {
	seznam *temp = najdi(head, steviloZa);
	if (temp == tail) {
		vstavi_za_repom(head, tail, stevilo);
		return;
	}
	if(temp == NULL){
		std::cout << "Napaka, el. ne obstaja" << std::endl;
		return;
	}
	seznam *priv = new seznam;
	priv->key = stevilo;
	priv->next = temp->next;
	priv->prev = temp;
	temp->next->prev = priv;
	temp->next = priv;
}

void brisi(seznam *&head, seznam *&tail, int stevilo) {
	seznam *temp = najdi(head, stevilo);
	if (temp->prev == NULL && temp->next == NULL) {
		head = NULL;
		tail = NULL;
	}
	else {
		if (temp->prev != NULL) temp->prev->next = temp->next;
		else {
			head = temp->next;
			head->prev = NULL;
		}
		if (temp->next != NULL) temp->next->prev = temp->prev;
		else {
			tail = temp->prev;
			tail->next = NULL;
		}
	}
	delete temp;
}
void izpisi_glava_do_rep(seznam *&head) {
	seznam *temp = head;
	while (temp != NULL) {
		std::cout << temp->key << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

void izpisi_rep_do_glava(seznam *&tail) {
	seznam *temp = tail;
	while (temp != NULL) {
		std::cout << temp->key << " ";
		temp = temp->prev;
	}
	std::cout << std::endl;
}

void testiranje_hitrosti(int stevilo) {
	seznam *head = NULL;
	seznam *tail = NULL;

	auto start = std::chrono::steady_clock::now();
	for (int i = 1; i <= stevilo; i++) {				//PRVI DEL (SEZNAM)
		vstavi_v_glavo(head, tail, i);
	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "Cas trajanja (seznam): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekundi." << std::endl;


	start = std::chrono::steady_clock::now();
	seznam *temp = head;								//DRUGI DEL (VSOTA SEZNAMA)
	long long vsota = 0;
	while (temp != NULL) {
		vsota = vsota + temp->key;
		temp = temp->next;
	}
	end = std::chrono::steady_clock::now();
	std::cout << "Vsota: " << vsota << std::endl;
	std::cout << "Cas trajanja (vsota seznama): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekundi." << std::endl;

	start = std::chrono::steady_clock::now();			//TRECI DEL (POLJE OD NAPREJ PREMA DESNO)
	int *polje = new int[stevilo];
	for (int i = 0; i < stevilo; i++) {
		for (int j = i; j > 0; j--) {
			polje[j] = polje[j - 1];
		}
		polje[0] = i + 1;
	}
	end = std::chrono::steady_clock::now();
	std::cout << "Cas trajanja (polje): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekundi." << std::endl;

	start = std::chrono::steady_clock::now();			//CETRTI DEL (VSOTA POLJA)
	vsota = 0;
	for (int i = 0; i < stevilo; i++) {
		vsota = vsota + polje[i];	
	}
	end = std::chrono::steady_clock::now();
	std::cout << "Vsota: " << vsota << std::endl;
	std::cout << "Cas trajanja (vsota polja): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekundi." << std::endl;

	start = std::chrono::steady_clock::now();			//PETI DEL (POLJE PREMA IZA)
	for (int i = 0; i < stevilo; i++) {
		polje[i] = i+1;
	}
	end = std::chrono::steady_clock::now();
	std::cout << "Cas trajanja (polje - konec): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekundi." << std::endl;

	seznam *priv = head;
	while (priv != NULL) {
		seznam *priv2 = priv;
		priv = priv->next;
		delete priv2;
	}
	delete[] polje;
}

int main() {


	bool running = true;
	int number = 0;
	char menu_value = 0;
	seznam *head = NULL;
	seznam *tail = NULL;
	do {
		int menu_value = menu();
		switch (menu_value) {
		case '1': {
			int stevilo;
			std::cout << "Vnesi trazeno stevilo: ";
			std::cin >> stevilo;
			seznam *novo;
			novo = najdi(head, stevilo);
			if (novo == 0) std::cout << "Stevilo ne obstaja." << std::endl;
			else std::cout << "Stevilo obstaja." << std::endl;
			break;
		}
		case'2': {
			int stevilo;
			std::cout << "Vnesi zeleno stevilo za vnos v glavo: ";
			std::cin >> stevilo;
			vstavi_v_glavo(head, tail, stevilo);
			break;
		}
		case '3': {
			int stevilo;
			std::cout << "Vnesi zeleno stevilo za vnos: ";
			std::cin >> stevilo;
			int steviloza;
			std::cout << "Vnesi za katerim stevilom zelite vnesti: ";
			std::cin >> steviloza;
			vstavi_za_elementom(head, tail, stevilo, steviloza);
			break;
		}
		case '4': {
			int stevilo;
			std::cout << "Vnesi zeleno stevilo za vnos: ";
			std::cin >> stevilo;
			vstavi_za_repom(head, tail, stevilo);
			break;
		}
		case '5': {
			int stevilo;
			std::cout << "Vnesi katero stevilo zelite zbrisati: ";
			std::cin >> stevilo;
			brisi(head, tail, stevilo);
			break;
		}
		case '6': {
			izpisi_glava_do_rep(head);
			break;
		}
		case '7': {
			izpisi_rep_do_glava(tail);
			break;
		}
		case '8': {
			int stevilo;
			std::cout << "Stevilo elementov: ";
			std::cin >> stevilo;
			testiranje_hitrosti(stevilo);
			break;
		}
		case '9': {
			running = false;
			break;
		}
		default: {
			std::cout << "Napaka!" << std::endl;
			break;
		}
		}
		
	} while (running);

	seznam *priv = head;
	while (priv != NULL) {
		seznam *priv2 = priv;
		priv = priv->next;
		delete priv2;
	}

	system("pause");
	return 0;
}