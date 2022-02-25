#include <iostream>
using namespace std;

int main() {
	int x[10], y[10], z[10];
	int stolpci[3] = { *x,*y,*z };
	x[10] = { 1,2,3,4,5,6,7,8,9,10 };
	y[10] = { 1,2,3,4,5,6,7,8,9,10 };
	z[10] = { 1,2,3,4,5,6,7,8,9,10 };

	int number;
	cin >> number;
	if (number == 1) {
		for (int i = 0; i < 3; i++) {
			cout << stolpci[i] << endl;
		}
	}


	system("pause");
	return 0;
}