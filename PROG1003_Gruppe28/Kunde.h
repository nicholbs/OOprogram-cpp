#ifndef Kunde_h
#define Kunde_h
//#pragma once

#include <vector>
#include <string>
#include "boligtype.h"
#include "Soner.h"


using namespace std;

//enum boligtype {Leilighet, Bolig};

class Kunde
{
	private:
		int ID, telefon;
		string navn, gateAddresse, postAdresse, mail;
		boligtype boligType;
		vector<int> kundeSoner;
	public:
		Kunde(int nr);
		Kunde(std::ifstream & inn, int kId);
		int kundeIdRetur();
		void endreData();
		void registrerSoner();
		void skrivData();
		void skrivTilFil(std::ofstream & ut);

		vector <int> kundeSonerRetur();
		~Kunde(); //Brukes til midlertidig test

};

#endif

