#pragma once
#include <string>
#include <fstream>
#include "Enum.h"
#include <fstream>
#include <vector>


class Bolig
{
protected:
	boligtype boligType;
	int pris;
	std::string beskrivelse;

private:
	int ID, dato, byggeaar, bruttoareal, antallSoverom;
	std::string navnSaksbehandler, navnEier, gateadresse, postadresse;

public:
	Bolig(int id);			//Konstruktor for manuelt lagde oppdrag
	Bolig(std::ifstream& inn);	//Konstruktor for lesing fra fil

	int getID();
	void skrivData();
	void skrivTilFil(std::ofstream& ut);		//Er denne nødvendig?? Ja ser ut til at den er brukt i Enebolig::skrivTilFIl
	void skrivTilKundeFil(std::ofstream& ut);
	bool erEnebolig();
};

