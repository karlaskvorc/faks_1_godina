#include <iostream>
using namespace std;

int push(int *s, int x, int &vrh, int max) {	//&VRH - FUNKCIJA PRIMA ADRESU OD VARIJABLE
	if (max == vrh + 1) return 0;				//VRH+1 JE ZATO KAJ POCNEMO S VRHOM OD -1 ; CE JE MAX ENAK VRH+1
	else {										//TO POMENI KAJ SMO PRISLI NA KONEC SKLADA IN JE ON PON
		vrh = vrh + 1;							//UNOS V POLJE
		s[vrh] = x;
		return 1;
	}
}


int pop(int *s, int &vrh) {
	if (vrh == -1) return -1;					//DELAMO S PRIRODNIM STEVILIMA ZATO IMAM RETURN -1 KER VSA
	else {										//OSTALA STEVILA MOREJU DOJTI
		vrh = vrh - 1;
		return s[vrh + 1];						//VRNEMO STEVILO OD PREDI IN SMANJIMO STEVILO V POLJU
	}
}


void izpisi_sklad(int *s, int &vrh) {
	cout << "Sklad: " << endl;
	for (int i = 0; i <= vrh; i++) {			//MANJI ALI ENAKO JE KER VKLJUCUJEMO IN VRH
		cout << s[i] << " ";
	}
	cout << endl;
}


int vpisi(int *q, int x, int &glava, int &rep, int max) {
	int novi_rep;
	novi_rep = (rep + 1) % max;					//DRUGACE NEGO NA PSEUDU KER JE REDOSLIJED OPERACIJ DRUGACI
	if (glava == novi_rep) return 0;			//VPRASAMO DAL JE GLAVA ENAKA NOVOM REPU, AK JEJE POTEM SMO
	else {										//PRISLI NA KONEC IN JE VRSTA POLNA
		q[rep] = x;
		rep = novi_rep;
		return 1;
	}
}


int beri(int *q, int &glava, int &rep, int max) {
	int prvi;
	if (glava == rep) return -1;				//DELAMO Z NARAVNIM STEVILIMA PA JE ZATO RETURN -1
	else {
		prvi = q[glava];
		glava = (glava + 1) % max;				//DRUGACE NEGO NA PSEUDU KER JE REDOSLIJED OPERACIJ DRUGACI
		return prvi;
	}
}


void izpisi_vrsto(int *q, int &glava, int &rep, int max) {
	cout << "Vrsta: " << endl;
	if (rep < glava) {							//CE JE REP MANJSI OD GLAVE POTEM ISPISUJEM OD GLAVE DO MAXA IN
		for (int i = glava; i < max; i++) {		//OD POCETKA DO REPA
			cout << q[i] << " ";
		}
		for (int i = 0; i < rep; i++) {
			cout << q[i] << " ";
		}
	}
	else {										//A CE JE GLAVA MANJSKA OD REPA, POTEM ISPISUJEM OD GLAVE DO REPA
		for (int i = glava; i < rep; i++) {
			cout << q[i] << " ";
		}
	}
	cout << endl;
}


int main() {
	int a, max,broj,x;
	int s[100], q[100];
	int vrh = -1, stevilo = 0, glava = 0, rep = 0;

	cout << "Vnesi velikost polja: ";
	cin >> a;
	if (a > 100) max = 100;
	else max = a;

	while (stevilo != 7) {						//PETLJA SE IZVODI TAK DOLGO DOK SE NE VNESE 7 (KONEC)
		cout << "Sklad-izbira:" << endl;		//SKLAD IZBIRA
		cout << "1) Vnos podatka" << endl;
		cout << "2) Branje podatka" << endl;
		cout << "3) Izpis vsebine sklada" << endl << endl;
		cout << "Krozna vrsta-izbira:" << endl;
		cout << "4) Vnos podatka:" << endl;
		cout << "5) Branje podatka" << endl;
		cout << "6) Izpis vrste od glave do repa" << endl;
		cout << "7) Konec" << endl << endl;


		cin >> stevilo;


		if (stevilo == 1) {
			cout << "Vnesi stevilo v sklad: ";
			cin >> x;
			broj = push(s, x, vrh, max);
			if (broj == 0) {
				cout << "Napaka -> POLNO!" << endl;
				continue;
			}
		 }

		if (stevilo == 2) {
			broj = pop(s, vrh);
			if (broj == -1) {
				cout << "Napaka -> PRAZNO!" << endl;
				continue;
			}
			else {
				cout << broj << endl;
				continue;
			}
		}

		if (stevilo == 3) izpisi_sklad(s, vrh);

		if (stevilo == 4) {
			cout << "Vnesi stevilo v vrsto: ";
			cin >> x;
			broj = vpisi(q, x, glava, rep, max);
			if (broj == 0) {
				cout << "Napaka -> POLNO!" << endl;
				continue;
			}
		}

		if (stevilo == 5) {
			broj = beri(q, glava, rep, max);
			if (broj == -1) {
				cout << "Napaka - PRAZNO!" << endl;
				continue;
			}
			else {
				cout << broj << endl;
				continue;
			}
		}
		
		if (stevilo == 6) izpisi_vrsto(q,glava,rep,max);
	}
	cout << "Nasvidanje" << endl;


	system("pause");
	return 0;
}