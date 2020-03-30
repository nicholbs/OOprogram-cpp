#include "Bolig.h"
#include "LesData3.h"
#include <iostream>
#include <istream>
#include <iomanip>
#include <fstream>		//kanskje denne ikke trengs
#include <string>		//lesFraFil

Bolig::Bolig(int id) {
	ID = id;
	boligType = boligtype::Leilighet;

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
}

Bolig::Bolig(ifstream& inn)
{
	boligType = boligtype::Leilighet;

	inn >> ID;
	inn.ignore();
	getline(inn, gateadresse);
	getline(inn, postadresse);
	getline(inn, navnEier);
	getline(inn, navnSaksbehandler);
	inn >> dato >> bruttoareal >> antallSoverom >> byggeaar;
	inn.ignore();
	getline(inn, beskrivelse);
	inn >> pris;
	inn.ignore();
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
	if (boligType == boligtype::Leilighet)
		cout << "\nLeilighet ";
	else
		cout << "\nEnebolig ";
	
	cout << "nr " << ID << ", annonse lagt inn " << dato << '\n'
		<< "Adresse: " << gateadresse << ", " << postadresse << "\n\n"
		<< setw(15) << left << "Eier: " << navnEier << '\n'
		<< setw(15) << left << "Saksbehandler: " << navnSaksbehandler << "\n\n"
		<< "Bruttoareal " << bruttoareal << " kvm med " << antallSoverom << " soverom."
		<< " Bygd " << byggeaar << ".\n" << '\"' << beskrivelse << "\"\n";

	if(boligType == boligtype::Leilighet)
		cout << "Pris: " << pris << " NOK\n\n";
}

void Bolig::skrivTilFil(ofstream& ut) {
	if (boligType == boligtype::Leilighet)
		ut << "L ";
	else
		ut << "E ";
	ut << ID << '\n';

	ut	<< gateadresse << '\n' << postadresse << '\n'
		<< navnEier << '\n' << navnSaksbehandler << '\n'
		<< dato << ' ' << bruttoareal << ' '
		<< antallSoverom << ' ' << byggeaar << '\n'
		<< beskrivelse << '\n' << pris << '\n';
}

void Bolig::skrivTilFil(ofstream& ut, vector <int> interesseSone) {
	if (boligType == boligtype::Leilighet)
	{
		ut << "Leilighet" << endl;
	}
	else
	{
		ut << "Enebolig" << endl;
	}


	ut << ID << ' ' << navnSaksbehandler << endl;
	ut << dato << ' ' << navnEier << endl;
	ut << byggeaar << ' ' << gateadresse << endl;
	ut << bruttoareal << ' ' << postadresse << endl;
	ut << antallSoverom << ' ' << beskrivelse << endl;
	ut << pris << endl;

	for (int i = 0; i < interesseSone.size(); i++)
	{
		ut << interesseSone[i];
	}
	ut << endl;
}

bool Bolig::erEnebolig()
{
	return (boligType == boligtype::Enebolig);
}