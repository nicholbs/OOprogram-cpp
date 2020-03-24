#include "Bolig.h"
#include <iostream>
#include <istream>

Bolig::Bolig(int id) {
	ID = id;
	boligType = boligtype::Leilighet;
	lesData();
}

Bolig::Bolig(int id, boligtype bt){
	ID = id;
	boligType = bt;
	lesData();
}

Bolig::~Bolig() {
	cout << "Bolig destruert" << endl;
}

int Bolig::getID() {
	return ID;
}

void Bolig::lesData()
{
	/*cout << "Dato: ";
	getline(cin, dato);
	cout << "Byggeår: ";
	getline(cin, byggeaar);
	cout << "Bruttoareal: ";
	getline(cin, navnEier);
	cout << "Soverom: ";
	getline(cin, navnEier);
	cout << "Pris: ";
	getline(cin, navnEier);

	cout << "Saksbehandler: ";
	getline(cin, navnEier);*/
	cout << "Eier: ";
	getline(cin, navnEier);
	/*cout << "Gateadresse";
	getline(cin, navnEier);
	cout << "Postadresse: ";
	getline(cin, navnEier);
	cout << "Kort beskrivelse: ";
	getline(cin, navnEier);*/
}

void Bolig::skrivData() {
	
}