#include <iostream>
using namespace std;


int push(int *s, int x, int &vrh, int max) {				//FUNKCIJA ZA VSAVLJANJE V SKLAD
	if (max == vrh + 1) return 0;
	else {									
		vrh = vrh + 1;							
		s[vrh] = x;
		return 1;
	}
}


int pop(int *s, int &vrh) {									//FUNKCIJA ZA BRISANJE Z SKLADA
	if (vrh == -1) return -1;					
	else {										
		vrh = vrh - 1;
		return s[vrh + 1];						
	}
}


int vracanje(int *iz, int *v,int &vrhiz,int &vrhv,int max) {//FUNKCIJA V KATEROJ ZEMEMO Z ENOGA STOLPA IN
	int b = pop(iz, vrhiz);									//IN VSTAVIMO V ZELENI STOLA (b varijabla)			
	if (b == -1) return 0;									//IN MI PREVERAVA DAL MI JE ZELENI STOLP PUNI
	int a = push(v, b, vrhv, max);							//ALI PRAZEN
	if (a == 0) return 0;
	else return 1;
}

void print(int *s, int &vrh) {								//ISPISUJEMO SKLAD

	for (int i = 0; i <= vrh; i++) {						//ISPISUJEMO BROJE UZ SKLAD
		cout << s[i] << " ";
	}
	cout << endl << endl;
	for (int i = vrh; i >= 0; i--) {
		cout << "\t";
		for (int j = 0; j < s[i]; j++) cout << "*";
		cout << endl;
	}
	cout << endl;
}


int main() {
	int x[10], y[10], z[10];								//POLJA ZA STOLPE
	int *polje[3] = { x,y,z };								//VEKSE POLJE Z STOLPIMA
	int max = 0;
	int vrh[3] = { -1,-1,-1 };								//POLJE Z VRHIMA

	while (max > 10 || max < 1) {
		cout << "Number of plates (1-10): ";				//NAJ BODO BROJ PLOSCICA MED 1 IN 10
		cin >> max;
	}


	int nm = max;
	for (int i = 0; i < max; i++) {
		if (push(x, nm, vrh[0], max) == 0) break;			//ISPOLNIM PRVI STOLP
		else {
			nm--;
			continue;
		}
	}

	while (vrh[2] != max-1) {								//PROGRAM RUNNA TAK DOLGO DOK NA ZADNJEM STOLPU NEJE
		int rowf, rowt,number;								//MAX STEVILO PLOSCIC
		cout << "___________________________________________" << endl << endl;
		cout << "stack 1: ";
		print(x, vrh[0]);									//ISPISUJEM STOLPE SAKI POT
		cout << endl << "stack 2: ";
		print(y, vrh[1]);
		cout << endl << "stack 3: ";
		print(z, vrh[2]);

		cout << "FROM:\t ";									//VPISUJEM IZ KATEREN V KATERI STOLP ZELIM PREMESTITI
		cin >> rowf;
		cout << "TO:\t ";
		cin >> rowt;
		int row1 = rowf - 1;
		int row2 = rowt - 1;
		
		if (polje[row1][vrh[row1]] < polje[row2][vrh[row2]] || vrh[row2]==-1) {		//PREVERAVA MI DAL JE ZADNJI V ODABRANOM STOLPCU MANJSI KOT
			number = vracanje(polje[row1], polje[row2], vrh[row1], vrh[row2], max);	//ZADNJI (VRH) NA ZELENOM STOLPU ALI MI JE TOTI ZELENI STOLP PRAZEN
			if (number == 0) {														//PREVERAVAM DAL MI JE STOLP POLNI AMPAK MI JE ODABRANI STOLP PRAZEN
				cout << "Napaka! Poskusi ponovo!" << endl;
				continue;
			}
		}
		else {
			cout << "Napaka! Poskusi ponovo!" << endl;
			continue;
		}

	}
	cout << endl << "PRISLI STE DO KONCA IGRE! :)" << endl;
	system("pause");
	return 0;
}