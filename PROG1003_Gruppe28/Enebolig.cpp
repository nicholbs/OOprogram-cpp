#include "Enebolig.h"
#include <iostream>

using namespace std;

Enebolig::Enebolig(int id) : Enebolig::Bolig(id) {
	cout << "Areal: ";
	cin >> areal;
	cout << "Festetomt [J/N]: ";
	char valg; cin >> valg;
	if (toupper(valg) == 'J')
		festetomt = true;
	else
		festetomt = false;
}
Enebolig::~Enebolig() {
	cout << "Enebolig destruert" << endl;
}