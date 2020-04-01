#include "Enebolig.h"
#include "LesData3.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
*  Konstruktor som kjøres når en Enebolig opprettes manuelt.
*
*  @param inn  -  Oppdragets ID
*  @see Bolig::Bolig(int id)
**/
Enebolig::Enebolig(int id) : Enebolig::Bolig(id) 
{
	boligType = boligtype::Enebolig;
	areal = lesInt("Areal", 1, 1000);
	cout << "Festetomt [J/N]: ";
	char valg; cin >> valg;
	if (toupper(valg) == 'J')
		festetomt = true;
	else
		festetomt = false;
}

/**
*  Konstruktor som kjøres når en Enebolig opprettes fra fil.
*
*  @param inn  -  Oppdragets ID
*  @see Bolig::Bolig(ifstream& inn)
**/
Enebolig::Enebolig(ifstream& inn) : Enebolig::Bolig(inn)
{
	boligType = boligtype::Enebolig;

	int a; inn >> a;
	festetomt = (a ? true : false);
	
	inn >> areal;
	inn.ignore();
}

/**
*  Skriver data spesifikke til underklassen Enebolig til terminal eller leselig fil.
*
*  @param ut  -  ostream som skal skrives til; i.e. cout eller fil
*  @see Bolig::skrivData(..)
**/
void Enebolig::skrivData(ostream& ut)
{
	Bolig::skrivData(ut);
	ut << left << setw(25) << "\nAreal: " << areal << " kvm"
		<< setw(25) << "\nFestetomt: " << (festetomt ? "Ja" : "Nei")
		<< "\n\n\"" << beskrivelse << "\"";
}

/**
*  Skriver data spesifikke til underklassen Enebolig til fil.
*
*  @see Bolig::skrivTilFil()
**/
void Enebolig::skrivTilFil(ofstream& ut)
{
	Bolig::skrivTilFil(ut);
	ut  << (festetomt ? '1' : '0')
		<< ' ' << areal << '\n';
}
