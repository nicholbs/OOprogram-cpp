#include <vector>
#include <string>
#include <iostream>
#include <ctype.h>
#include "Soner.h"
#include "Kunder.h"

using namespace std;

void menyKunde();
void menySone();
void menyOppdrag();

Soner gSoner;
Kunder gKunder;

int main()
{
	char kommando1;
	cin >> kommando1;

	while (1) {
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
			exit(1);
		}
		cin >> kommando1;
	}
}

void menyKunde() {
	char kommando2;
	cin >> kommando2;

	switch (toupper(kommando2)) {
	case 'N':
		//Lage ny Kunde
		cout << "Ny kunde" << endl;
		break;
	case '1':
		//Skriv ut info om enkelt Kunde
		//Stans utskrift hver 10. sone
		cout << "Skriv info om en kunde" << endl;
		break;
	case 'A':
		//Skriv ut ALLE Kunder
		cout << "Skriv info om alle kunder" << endl;
		break;
	case 'E':
		//Skriv ut info om Kunde
		//Bruker kan legge til/slette soner fra kunden | NB SORTER VECTOR
		cout << "Endre info om kunde" << endl;
		break;
	case 'S':
		//Slett kunde | HUSK PEKER
		cout << "Slett kunde" << endl;
		break;
	case 'O':
		//Skriv all data om alle boliger i alle kundens interessesoner til FIL
		//Filnavn: K[kundenr].DTA
		cout << "Skriv all bolig data" << endl;
		break;
	default:
		cout << "Kunde Default" << endl;
	}
}

void menySone() {
	char kommando2;
	cin >> kommando2;

	switch (toupper(kommando2)) {
	case 'N':
		int snr; cin >> snr;
		gSoner.nySone(snr);
		break;
	case '1':
		//Skriv ut alt om alle oppdrag
		//Stans utskrift hver 5. sone
		break;
	case 'A':
		//Skriv HOVEDDATAENE om alle soner til terminal
		//nr, beskrivelse, antall oppdrag
		break;
	default:
		cout << "Sone Default" << endl;
	}
}

void menyOppdrag() {
	char kommando2;
	cin >> kommando2;

	switch (toupper(kommando2)) {
	case 'N':
		int snr; cin >> snr;
		gSoner.nyBolig(snr);
		break;
	case '1':
		//Alt om oppdrager skrives ut
		break;
	case 'S':
		//Slett oppdrag
		//Bruker skal BEKREFTE at de vil slette før det gjøres
		break;
	default:
		cout << "Oppdrag Default" << endl;
	}
}