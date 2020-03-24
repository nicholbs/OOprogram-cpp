#ifndef Kunde_h
#define Kunde_h
//#pragma once

#include <vector>
#include <string>


using namespace std;

enum boligtype {Leilighet, Bolig};

class Kunde
{
	private:
		int ID, telefon;
		string navn, gateAddresse, postAdresse, mail;
		boligtype boligType;
		vector<int> soner;
	public:
		Kunde(int nr);
		int kundeIdRetur();
		void skrivData();
};

#endif

