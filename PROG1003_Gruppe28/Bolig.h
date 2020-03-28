#pragma once
#include <string>
#include <fstream>			
#include "boligtype.h"
#include <fstream>			
#include <vector>

using namespace std;

class Bolig
{
protected:
	boligtype boligType;
	int pris;

private:
	int ID, dato, byggeaar, bruttoareal, antallSoverom;
	string navnSaksbehandler, navnEier, gateadresse, postadresse, beskrivelse;
	
public:
	Bolig(int id);
	Bolig(ifstream& inn);
	~Bolig();
	int getID();
	void skrivData();
	void skrivTilFil(ofstream& ut);
	void skrivTilFil(ofstream& ut, vector <int> interesseSone);
	bool erEnebolig();
};

