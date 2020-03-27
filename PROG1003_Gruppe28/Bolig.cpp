#include "Bolig.h"
#include "LesData3.h"
#include <iostream>
#include <istream>
#include <iomanip>
#include <fstream>		//kanskje denne ikke trengs

Bolig::Bolig(int id) {
	ID = id;

	cin.ignore();
	dato = lesInt("Dato [YYYYMMDD]: ", 0, 99999999);
	byggeaar = lesInt("Byggeaar: ", 0, 2020);
	bruttoareal = lesInt("Bruttoareal: ", 0, 10000);
	antallSoverom = lesInt("Soverom: ", 1, 20);
	pris = lesInt("Pris: ", 0, 1000000000);

	cout << "Saksbehandler: ";
	getline(cin, navnSaksbehandler);
	cout << "Eier: ";
	getline(cin, navnEier);
	cout << "Gateadresse: ";
	getline(cin, gateadresse);
	cout << "Postadresse: ";
	getline(cin, postadresse);
	cout << "Kort beskrivelse: ";
	getline(cin, beskrivelse);

	boligType = boligtype::Leilighet;
}

Bolig::~Bolig() {
	cout << "\nSlettet ";
	if (boligType == boligtype::Leilighet)
		cout << "leilighet";
	else
		cout << "enebolig";
	cout << " med ID " << ID << ".\n";
}

int Bolig::getID() {
	return ID;
}

void Bolig::skrivData() {
	cout << "\nBolignummer " << ID << ", annonse lagt inn " << dato << '\n'
		<< gateadresse << ", " << postadresse << "\n\n"
		<< setw(15) << "Eier: " << navnEier << '\n'
		<< setw(15) << "Saksbehandler: " << navnSaksbehandler << "\n\n"
		<< "Bruttoareal " << bruttoareal << " kvm med " << antallSoverom << " soverom."
		<< "Bygd i " << byggeaar << ".\n" << '\"' << beskrivelse << "\"\n\n"
		<< "  " << pris << " NOK\n\n";
}


void Bolig::skrivTilFil(ofstream& ut, vector <int> interesseSone) {
	ut << ID << ' ' << navnSaksbehandler << endl;
	ut << dato << ' ' << navnEier << endl;
	ut << byggeaar << ' ' << gateadresse << endl;
	ut << bruttoareal << ' ' << postadresse << endl;
	ut << antallSoverom << ' ' << beskrivelse << endl;
	ut << pris << ' ';

	if (boligType == boligtype::Leilighet)
		{
		ut << "Leilighet" << endl;
		}
	else
		{
		ut << "Enebolig" << endl;
		}
	
	for (int i = 0; i < interesseSone.size(); i++)
	{
		ut << interesseSone[i];
	}
	ut << endl;
}


void lesFraFil(ifstream& inn) {


}