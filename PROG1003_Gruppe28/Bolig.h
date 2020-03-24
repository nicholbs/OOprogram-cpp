#pragma once
#include <string>
using namespace std;

enum class boligtype{Leilighet, Enebolig};

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

