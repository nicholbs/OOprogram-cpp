#include <vector>
#include <string>
#include <iostream>
#include <ctype.h>		//toupper()
#include "Soner.h"
#include "Kunder.h"
#include "Kunde.h"		//nicholas la til for testing i K O <knr>
#include "Bolig.h"		//K O <knr>
#include <iomanip>
#include "LesData3.h"
#include <fstream>		//K O <knr>

using namespace std;

void menyKunde();
void menySone();
void menyOppdrag();

void hovedMeny();		//utskrift av kommandoer for Kunder, Soner og Oppdrag/bolig
void kundeMeny();		//utskrift av kommandoer for Kunder: N, 1, A, E, S og O
void soneMeny();		//utskrift av kommandoer for Soner: N, 1 og A
void oppdragMeny();		//utskrift av kommandoer for Oppdrag: N, 1 og S

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
			break;
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

/**
*	Meny for Sone basert på input
*
*	De forskjellige kommandoer er:
*	N - lager ny Sone
*	1 - skriver all informasjon om en sone	
*	A - skriver hoved data om alle soner
**/
void menySone() {
	soneMeny();
	char kommando2;
	int snr;

	cin >> kommando2;
	switch (toupper(kommando2)) {
	case 'N':		
		cin >> snr;
		gSoner.nySone(snr);
		break;
	case '1':
		//Skriv ut alt om alle oppdrag
		//Stans utskrift hver 5. sone
		break;
	case 'A':
		gSoner.skrivHovedDataAlleSoner();
		break;
	case 'F':	//TESTFUNKSJON - SKAL FJERNES
		gSoner.skrivTilFil();
		break;
	default:
		cout << "Sone Default" << endl;
	}
}

/**
*	Meny for Oppdrag basert på input
*
*	De forskjellige kommandoer er:
*	N - lager nytt oppdrag
*	1 - skriver informasjon om ett oppdrag
*	A - skriver all informasjon om alle oppdrag
*	S - Sletter spesifikt oppdrag
**/
void menyOppdrag() {

	oppdragMeny();
	char kommando2;
	int nr;
	cin >> kommando2;

	switch (toupper(kommando2)) {
	case 'N':
		cin >> nr;
		gSoner.nyttOppdrag(nr);
		break;
	case '1':
		cin >> nr;
		gSoner.skrivOppdrag(nr);
		break;
	case 'A':		//TESTCASE - SKAL FJERNES
		gSoner.skrivAlleOppdrag();
		break;
	case 'S':
		cin >> nr;
		gSoner.slettOppdrag(nr);
		break;
	default:
		cout << "Oppdrag Default" << endl;
	}
}

/**
* Utskrift av meny for hoved meny, med andre ord switch i main funksjonen
**/
void hovedMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(K)" << setw(30) << "for Kunde funksjoner" << endl;
	cout << setw(5) << "(S)" << setw(30) << "for Sone funksjoner" << endl;
	cout << setw(5) << "(O)" << setw(30) << "for Oppdrag/Bolig funksjoner" << endl;
	cout << endl;

}

/**
* Utskrift av meny for kunde funksjoner, kommer etter input "K" fra hovedMeny
**/
void kundeMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Kunde" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv info om en kunde" << endl;
	cout << setw(5) << "(A)" << setw(30) << "Skriv info om alle kunder" << endl;
	cout << setw(5) << "(E)" << setw(30) << "Endre info om kunde" << endl;
	cout << setw(5) << "(S)" << setw(30) << "Slett kunde" << endl;
	cout << setw(5) << "(O)" << setw(30) << "Skriver all bolig data" << endl;
	cout << endl;

}

/**
* Utskrift av meny for Sone funksjoner, kommer etter input "S" fra hovedMeny
**/
void soneMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Sone" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv ut alt om alle oppdrag" << endl;
	cout << setw(5) << "(A)" << setw(30) << "Hoveddata om alle soner" << endl;
	cout << endl;

}

/**
* Utskrift av meny for Oppdrag/Bolig funksjoner, kommer etter input "O" fra hovedMeny
**/
void oppdragMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Oppdrag" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv ut alt om alle oppdrag?? eller bare om et oppdrag" << endl;			///////////////Skal det skrives ut om en eller alle oppdrag??????????
	cout << setw(5) << "(S)" << setw(30) << "Slett oppdrag" << endl;
	cout << endl;

}
