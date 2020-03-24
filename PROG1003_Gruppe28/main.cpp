#include <vector>
#include <string>
#include <iostream>
#include <ctype.h>
#include "Soner.h"
#include "Kunder.h"
#include <iomanip>

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
	hovedMeny();

	char kommando1;
	cin >> kommando1;

	while (1) {
		switch (toupper(kommando1)) {
		
		case 'K':
			cout << setw(35) << "Du har valgt Kunde funksjoner" << endl;
			menyKunde();
			break;
		
		case 'S':
			cout << setw(35) << "Du har valgt Sone funksjoner" << endl;
			menySone();
			break;
		
		case 'O':
			cout << setw(35) << "Du har valgt Oppdrag/bolig funksjoner" << endl;
			menyOppdrag();
			break;
		
		default:
			exit(1);
		}
		cin >> kommando1;
	}
}

void hovedMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(K)" << setw(30) << "for Kunde funksjoner" << endl;
	cout << setw(5) << "(S)" << setw(30) << "for Sone funksjoner" << endl;
	cout << setw(5) << "(O)" << setw(30) << "for Oppdrag/Bolig funksjoner" << endl;
	cout << endl;

}

void kundeMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Kunde" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv info om en kunde" << endl;
	cout << setw(5) << "(A)" << setw(30) << "Skriv info om alle kunder" << endl;
	cout << setw(5) << "(E)" << setw(30) << "Endre info om kunde" << endl;
	cout << setw(5) << "(S)" << setw(30) << "Slett kunde" << endl;
	cout << setw(5) << "(O)" << setw(30) << "Skriv all bolig data" << endl;
	cout << endl;

}

void menyKunde() {
	kundeMeny();

	char kommando2;
	cin >> kommando2;

	switch (toupper(kommando2)) {
	case 'N':
		cout << setw(35) << "Du har Laget ny Kunde" << endl;
		//Lage ny Kunde
		cout << "Ny kunde" << endl;
		break;
	
	case '1':
		//Skriv ut info om enkelt Kunde
		//Stans utskrift hver 10. sone
		cout << setw(35) << "Skriv info om en kunde" << endl;
		break;
	
	case 'A':
		//Skriv ut ALLE Kunder
		cout << setw(35) << "Skriv info om alle kunder" << endl;
		break;
	
	case 'E':
		//Skriv ut info om Kunde
		//Bruker kan legge til/slette soner fra kunden | NB SORTER VECTOR
		cout << setw(35) << "Endre info om kunde" << endl;
		break;
	
	case 'S':
		//Slett kunde | HUSK PEKER
		cout << setw(35) << "Slett kunde" << endl;
		break;
	
	case 'O':
		//Skriv all data om alle boliger i alle kundens interessesoner til FIL
		//Filnavn: K[kundenr].DTA
		cout << setw(35) << "Skriv all bolig data" << endl;
		break;
	
	default:
		cout << setw(35) << "Kunde Default" << endl;
	}
}

void soneMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Sone" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv ut alt om alle oppdrag" << endl;
	cout << setw(5) << "(A)" << setw(30) << "Hoveddata om alle soner" << endl;
	cout << endl;

}

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
		//Skriv HOVEDDATAENE om alle soner til terminal
		//nr, beskrivelse, antall oppdrag
		break;
	default:
		cout << "Sone Default" << endl;
	}
}

void oppdragMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Oppdrag" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv ut alt om alle oppdrag?? eller bare om et oppdrag" << endl;			///////////////Skal det skrives ut om en eller alle oppdrag??????????
	cout << setw(5) << "(S)" << setw(30) << "Slett oppdrag" << endl;
	cout << endl;

}

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
	case 'S':
		//Slett oppdrag
		//Bruker skal BEKREFTE at de vil slette før det gjøres
		break;
	default:
		cout << "Oppdrag Default" << endl;
	}
}