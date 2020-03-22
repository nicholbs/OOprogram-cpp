// PROG1003_Gruppe28.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <string>
#include <iostream>

using namespace std;

void menyKunde();
void menySone();
void menyOppdrag();

int main()
{
	char kommando;
	cin >> kommando;

	switch (kommando) {
	case 'K':
		menyKunde();
	case 'S':
		menySone();
	case 'O':
		menyOppdrag();
	}
}

void menyKunde() {
	char kommando;
	cin >> kommando;

	switch (kommando) {
	case 'N':
		//Lage ny Kunde
	case '1':
		//Skriv ut info om enkelt Kunde
		//Stans utskrift hver 10. sone
	case 'A':
		//Skriv ut ALLE Kunder
	case 'E':
		//Skriv ut info om Kunde
		//Bruker kan legge til/slette soner fra kunden | NB SORTER VECTOR
	case 'S':
		//Slett bruker | HUSK PEKER
	case 'O':
		//Skriv all data om alle boliger i alle kundens interessesoner til FIL
		//Filnavn: K[kundenr].DTA
	}
}

void menySone() {
	char kommando;
	cin >> kommando;

	switch (kommando) {
	case 'N':
		//Lag ny sone
	case '1':
		//Skriv ut alt om alle oppdrag
		//Stans utskrift hver 5. sone
	case 'A':
		//Skriv HOVEDDATAENE om alle soner til terminal
		//nr, beskrivelse, antall oppdrag
	}
}

void menyOppdrag() {
	char kommando;
	cin >> kommando;

	switch (kommando) {
	case 'N':
		//Nytt oppdrag (Bolig/Enebolig) legges til med aktuelt snr (gitt at finnes)
		//Tildeles iterativt nummer
		//ALLE datamedlemmer leses inn
	case '1':
		//Alt om oppdrager skrives ut
	case 'S':
		//Slett oppdrag
		//Bruker skal BEKREFTE at de vil slette før det gjøres
	}
}