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
*  Konstruktor som kjøres når en Bolig opprettes manuelt. 
*
*  @param id  -  Boligens ID
*  @see lesGateAdr(..)
*  @see lesPostAdr(..)
**/
Bolig::Bolig(int id) {
	ID = id;
	boligType = boligtype::Leilighet;
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
*  Konstruktor som kjøres når en Bolig opprettes manuelt. 
*
* @param inn    -   Fil som skal skrives til (SONER.DTA)
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
*Denne klassefunksjonen returnerer Bolig sin ID
*
*@return ID  -  Boligens ID
**/
int Bolig::getID() {
	return ID;
}

/**
*  Skriver all data til en Bolig til terminal eller leselig fil.
*
*  @param ut  -  ostream som skal skrives til; i.e. cout eller fil
**/
void Bolig::skrivData(ostream& ut) {
	ut << " ~Oppdrag " << ID << ", ";
	if (boligType == boligtype::Leilighet)
		ut << "Leilighet~\n\n";
	else
		ut << "Enebolig~\n\n";

	ut << left << setw(24) << "Pris: " << pris << " NOK"
		<< setw(25) << "\nLagt ut: " << dato
		<< setw(25) << "\nEier: " << navnEier
		<< setw(25) << "\nSaksbehandler: " << navnSaksbehandler
		<< setw(25) << "\nGateadresse: " << gateadresse
		<< setw(25) << "\nPostadresse: " << postadresse
		<< setw(25) << "\nBruttoareal: " << bruttoareal << " kvm"
		<< setw(25) << "\nSoverom: " << antallSoverom
		<< setw(25) << "\nBygd: " << byggeaar;

	if (boligType != boligtype::Enebolig)		//Sørger for at beskrivelse alltid kommer til slutt
		ut << "\n\n\"" << beskrivelse << "\"";
}

/**
*  Skriver all data til en Bolig til en fil.
*
* @param ut  -  Fil som skal skrives til
**/
void Bolig::skrivTilFil(ofstream& ut) {
	if (boligType == boligtype::Leilighet)
		ut << "L " << ID << '\n';
	else
		ut << "E " << ID << '\n';;

	ut	<< gateadresse << '\n' << postadresse << '\n'
		<< navnEier << '\n' << navnSaksbehandler << '\n'
		<< dato << ' ' << bruttoareal << ' '
		<< antallSoverom << ' ' << byggeaar << '\n'
		<< beskrivelse << '\n' << pris << '\n';
}

/**
*  Sjekker om et oppdrag er av boligtype Enebolig.
*
*  @return bool - true hvis oppdraget er Enebolig, ellers false
*/
bool Bolig::erEnebolig()
{
	return (boligType == boligtype::Enebolig);
}
