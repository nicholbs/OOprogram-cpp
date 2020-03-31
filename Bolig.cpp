#include "Bolig.h"
#include "Funksjoner.h"
#include "LesData3.h"
#include <iostream>
#include <istream>
#include <iomanip>
#include <fstream>		//kanskje denne ikke trengs
#include <string>		//lesFraFil

using namespace std;

/**
*Denne klassefunksjonen registrerer en ny bolig
*
* @param id -   medsendt id
* @see lesGateAdr(..);
* @see lesPostAdr(..)
**/
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
	lesGateAdr(gateadresse);
	lesPostAdr(postadresse);
	cout << "Kort beskrivelse: ";
	getline(cin, beskrivelse);
}

/**
* Denne klassefunksjonen leser data fra fil
*
* @param inn    -   medsendt filobjekt for innlesning
* */
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

/**
* Bolig sin destructor
**/
Bolig::~Bolig() {
	cout << "\nSlettet ";
	if (boligType == boligtype::Leilighet)
		cout << "leilighet";
	else
		cout << "enebolig";
	cout << " med ID " << ID << ".\n";
}

/**
*Denne klassefunksjonen returnerer Bolig sin ID
*
*@return ID -   Boligens ID
**/
int Bolig::getID() {
	return ID;
}

/**
*Denne Klassefunksjonen skriver ut en Bolig
**/
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

/**
* Denne klassefunksjonen for Bolig skriver data ut til fil
*
* @param ut -   Et ofstream objekt for utskrift til fil
**/
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

/**
* Skriver boliginformasjon til kundefil p� leselig format.
*
* @param ut    -   fil data skal skrives til (Kxxxx.DTA)
**/

void Bolig::skrivTilKundeFil(ofstream& ut) {
	if (boligType == boligtype::Leilighet)
		ut << "Leilighet~\n";
	else
		ut << "Enebolig~\n";

	ut << left << setw(24) << "Pris: " << pris 
		<< setw(25) << "\nLagt ut: " << dato
		<< setw(25) << "\nEier: " << navnEier 
		<< setw(25) << "\nSaksbehandler: " << navnSaksbehandler
		<< setw(25) << "\nGateadresse: " << gateadresse 
		<< setw(25) << "\nPostadresse: " << postadresse
		<< setw(25) << "\nBruttoareal: " << bruttoareal 
		<< setw(25) << "\nSoverom: " << antallSoverom
		<< setw(25) << "\nBygd: " << byggeaar 
		<< "\n\n\"" << beskrivelse << "\"";
	ut << "\n-----------------------------------------------------\n";
}

/**
*
*/
bool Bolig::erEnebolig()
{
	return (boligType == boligtype::Enebolig);
}
