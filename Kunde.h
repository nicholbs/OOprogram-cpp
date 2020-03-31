#ifndef Kunde_h
#define Kunde_h
//#pragma once

#include <vector>
#include <string>
#include "Enum.h"
#include "Soner.h"



//enum boligtype {Leilighet, Bolig};

class Kunde
{
	private:
		int ID, telefon;
		std::string navn, gateAddresse, postAdresse, mail;
		boligtype boligType;
		std::vector<int> kundeSoner;
	public:
		Kunde(int nr);
		Kunde(std::ifstream & inn, int kId);
		int kundeIdRetur();
		string getNavn();
		void endreData();
		void registrerSoner();
		void skrivData();
		void skrivTilFil(std::ofstream & ut);

		std::vector <int> kundeSonerRetur();
		~Kunde(); //Brukes til midlertidig test

};

#endif

