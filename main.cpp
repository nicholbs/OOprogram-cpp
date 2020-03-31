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







Soner gSoner;
Kunder gKunder;


/**
* HovedProgrammet gir riktig meny basert på input.
* De forskjellige kommandoer er:
*
* K - utskrift av meny for kunde funksjoner
* S - utskrift av meny for Sone funksjoner 
* O - utskrift av meny for Oppdrag funksjoner 
* Q - Avslutt program
* */
int main()
{
	gSoner.lesFraFil();
	gKunder.kunderLesAlleFraFil();

	hovedMeny();

	bool loop = true;
	char kommando1;
	cin >> kommando1;

	while (loop) {
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
		case 'Q':
			loop = false;
			gSoner.skrivTilFil();
			gKunder.kunderSkrivAlleTilFil();
			break;
		default:
			hovedMeny();
		}
		cin >> kommando1;
	}
	return 0;
}

/**
*	Meny for Kunde basert på input
*
*	De forskjellige kommandoer er:
*	N - lager ny kunde
*	1 - skriver informasjon om en kunde
*	A - skriver hoveddata om alle kunder
*	E - Valgt kunde sin data skrives ut, for å så kunne bli endret
*	S - Sletter valgt kunde
*	O - All data om alle boliger i kundens interessesoner skrives på lesbart og forståelig format til filen Kxxxxx.DTA. Der «xxxxx» er kundens unike nummer.
**/
void menyKunde() {
	kundeMeny();

	char kommando2;
	cin >> kommando2;

	switch (toupper(kommando2)) {
	case 'N':
		gKunder.nyKunde();
		break;

	case '1':
		//Skriv ut info om enkelt Kunde
		//Stans utskrift hver 10. sone
		cout << setw(35) << "Skriv info om en kunde" << endl;
        gKunder.kundeSkrivData();
		break;

	case 'A':
		//Skriv ut ALLE Kunder
		cout << setw(35) << "Skriv info om alle kunder" << endl;
		gKunder.kundeSAlleSkrivData();
		break;

	case 'E':
		//Skriv ut info om Kunde
		//Bruker kan legge til/slette soner fra kunden | NB SORTER VECTOR
		cout << setw(35) << "Endre info om kunde" << endl;
		gKunder.kundeEndreData();
		break;

	case 'S':
		//Slett kunde | HUSK PEKER
		cout << setw(35) << "Slett kunde" << endl;
		gKunder.slettKunde();
		break;

	case 'O':			//K -kunde, O - Skriv ut all data om kundens interesseSone, <knr> -valgt kunde
		skrivUtInteresseSoner();
		break;

    case 'D':
        cout <<"\nTest skriv ut alle kunder til fil";
        gKunder.kunderSkrivAlleTilFil();
        cout <<"\nAlle skrevet til fil";
        break;
    case 'L':
        cout <<"\nTest imprt alle kunder fra fil";
        gKunder.kunderLesAlleFraFil();
        cout <<"\nFerdig";
		break;

	default:
		cout << setw(35) << "Kunde Default" << endl;
	}
}










