#pragma once
#include <string>
#include "boligtype.h"
#include <fstream>			//nicholas lagt til for skrivTilFil
using namespace std;

class Bolig
{
protected:
	boligtype boligType;

private:
	int ID, dato, byggeaar, bruttoareal, antallSoverom, pris;
	string navnSaksbehandler, navnEier, gateadresse, postadresse, beskrivelse;
	
public:
	Bolig(int id);
	~Bolig();
	int getID();
	void skrivData();
	void skrivTilFil(ofstream & ut);
};

