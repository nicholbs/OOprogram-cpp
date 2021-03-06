#include <vector>
#include <string>
#include <ctype.h>		//toupper()
#include <string>
#include <iostream>		//Library for cout/cin
#include "Soner.h"
#include "Kunder.h"
#include "Kunde.h"		//nicholas la til for testing i K O <knr>
#include "Bolig.h"		//K O <knr>
#include <iomanip>
#include "LesData3.h"
#include <fstream>		//K O <knr>
#include "Const.h"		//Brukes for Max konstanter
#include "Funksjoner.h"

using namespace std;

void menyKunde();

Soner gSoner;		///Globalt objekt for ? holde alle Sone og derunder Oppdrag
Kunder gKunder;		///Globalt objekt for ? holde alle Kunde


/**
* HovedProgrammet gir riktig meny basert p? input.
* De forskjellige kommandoer er:
*
* K - utskrift av meny for kunde funksjoner
* S - utskrift av meny for Sone funksjoner 
* O - utskrift av meny for Oppdrag funksjoner 
* Q - Avslutt program
* */
int main()
{
	char kommando1;

	gSoner.lesFraFil();
	gKunder.kunderLesAlleFraFil();
	
	hovedMeny();
	cout << "\nKommando: ";
	cin >> kommando1;

	while (kommando1 != 'Q' && kommando1 != 'q') {
		switch (toupper(kommando1)) {
		case 'K':
			menyKunde();
			break;
		case 'S':
			menySone();
			break;
		case 'O':
			menyOppdrag();
			break;
		default:
			hovedMeny();
		}
		cout << "\nKommando: ";
		cin >> kommando1;
	}
	gSoner.skrivTilFil();
	gKunder.kunderSkrivAlleTilFil();

	return 0;
}