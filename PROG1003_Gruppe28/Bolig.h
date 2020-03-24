#pragma once
#include <string>
#include "boligtype.h"
using namespace std;

class Bolig
{
	//int ID, dato, byggeaar, bruttoareal, antallSoverom, pris;
	int ID;
	//string navnSaksbehandler, navnEier, gateadresse, postadresse, beskrivelse;
	string navnEier;
	boligtype boligType;

public:
	Bolig(int id);
	Bolig(int id, boligtype bt);
	~Bolig();
	int getID();
	void lesData();
	void skrivData();
};

