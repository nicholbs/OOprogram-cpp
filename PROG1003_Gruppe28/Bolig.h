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
	Bolig();
	~Bolig();
	int getID();
	void skrivData();
	void skrivTilFil(ofstream& ut);		//Er denne nødvendig?? Ja ser ut til at den er brukt i Enebolig::skrivTilFIl
	void skrivTilFil(ofstream& ut, vector <int> interesseSone);
	void lesFraFil();
	bool erEnebolig();
};

