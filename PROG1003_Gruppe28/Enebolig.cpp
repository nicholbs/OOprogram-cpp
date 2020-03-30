#include "Enebolig.h"
#include "LesData3.h"
#include <iostream>

using namespace std;

Enebolig::Enebolig(int id) : Enebolig::Bolig(id) 
{
	boligType = boligtype::Enebolig;

	cout << "Areal: ";
	areal = lesInt("Areal", 1, 1000);
	cout << "Festetomt [J/N]: ";
	char valg; cin >> valg;
	if (toupper(valg) == 'J')
		festetomt = true;
	else
		festetomt = false;
}

Enebolig::Enebolig(ifstream& inn) : Enebolig::Bolig(inn)
{
	boligType = boligtype::Enebolig;

	int a; inn >> a;
	festetomt = (a ? true : false);
	
	inn >> areal;
	inn.ignore();
}

Enebolig::~Enebolig() {
	cout << "Enebolig destruert" << endl;
}

void Enebolig::skrivData()
{
	Bolig::skrivData();
	cout << "Areal: " << areal << '\n';
	if (festetomt)
		cout << "Festetomt\n";
	else
		cout << "Selveiet\n";
	cout << "Pris: " << pris << " NOK\n\n";
}

void Enebolig::skrivTilFil(ofstream& ut)
{
	Bolig::skrivTilFil(ut);
	ut  << (festetomt ? '1' : '0')
		<< ' ' << areal << '\n';
}
