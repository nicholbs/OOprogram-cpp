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
			continue;
		default:
			hovedMeny();
		}
		cin >> kommando1;
	}
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
		{
		int kundeNr;	//Variabel for å holde medsent int i kommando "K O <knr>"
		cin >> kundeNr;	//Innskriving av <knr> går til helvette om bruker taster bokstav og ikke tall
		cout << setw(35) << "Leter etter kunde med nr:" << ' ' << kundeNr << endl;


		if (gKunder.kundeListeTomSjekk() == false)
			{
			vector <int> kundeSoneInteresse;
			kundeSoneInteresse = gKunder.finnKundeSone(kundeNr);
			if (kundeSoneInteresse.empty() == false)
				{
				string navnPaFil = "K";
				string kunde = to_string(kundeNr);
				kunde.append(".DTA");
				string skrivTilFil = navnPaFil + kunde;
				ofstream utfilA(skrivTilFil);
				Bolig* boligPeker;

				for (int i = 0; i < kundeSoneInteresse.size(); i++)        //Utskrift av vector sin data
					{
						boligPeker = (gSoner.finnOppdrag(kundeSoneInteresse.at(i)));
						if (boligPeker == nullptr)
							{
							cout << setw(35) << "Det er ikke blitt skrevet til fil" << endl;
							}
						else
							{
							cout << setw(35) << "Skriver Bolig:" << ' ' << kundeSoneInteresse.at(i) << endl;
							boligPeker->skrivTilFil(utfilA, kundeSoneInteresse);			//Er det dust å skrive ut for hver bolig at de er del av kunden sine interesse sone?
							}
					}

				}
			else
				{
				cout << setw(35) << "Kunden fantes, men han har ikke registrert noen soner:" << endl;
				}
			}
		else
			{
			cout << setw(35) << "Det finnes ingen kunder i hele tatt" << endl;
			}
		}
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










