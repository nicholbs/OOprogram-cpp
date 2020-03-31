#include "Enebolig.h"
#include "LesData3.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
*  Konstruktor som kjøres etter når en Enebolig opprettes manuelt.
*
*  @param inn  -  Oppdragets ID
*  @see Bolig::Bolig(int id)
**/
Enebolig::Enebolig(int id) : Enebolig::Bolig(id) 
{
	boligType = boligtype::Enebolig;
	//////////////////////////////////////Oddbjørn lag en sjekk på areal
	cout << "Areal: ";
	areal = lesInt("Areal", 1, 1000);
	cout << "Festetomt [J/N]: ";
	char valg; cin >> valg;
	if (toupper(valg) == 'J')
		festetomt = true;
	else
		festetomt = false;
}

/**
*  Konstruktor som kjøres etter når en Enebolig opprettes fra fil.
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
*  Skriver data spesifikke til underklassen Enebolig til terminalen.
*
*  @see Bolig::skrivData()
**/
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

/**
*  Skriver boliginformasjon til kundefil på leselig format.
*
*  @param ut  -  fil data skal skrives til (Kxxxx.DTA)
*  @see Bolig::skrivTilKundeFil(..)
**/
void Enebolig::skrivTilKundeFil(std::ofstream& ut)
{
	Bolig::skrivTilKundeFil(ut);
	ut	<< left << setw(25) << "\nAreal: " << areal
		<< setw(25) << "\nFestetomt: " << (festetomt ? "Ja" : "Nei")
		<< "\n\n\"" << beskrivelse << "\"";
}
