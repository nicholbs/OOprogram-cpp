#pragma once
#include "Bolig.h"
class Enebolig : public Bolig
{
	int areal;
	bool festetomt;

public:
	Enebolig(int id);			//Konstruktor for manuelt lagde oppdrag
	Enebolig(std::ifstream& inn);	//Konstruktor for lesing fra fil
	~Enebolig();
	void skrivData();
	void skrivTilFil(std::ofstream& ut);
};

