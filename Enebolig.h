#ifndef __Enebolig_H
#define __Enebolig_H
#include "Bolig.h"

/**
 * Klasse Enebolig er underklasse av Bolig, Enebolig blir også lagret i Sone.
 *
 * Enebolig har et par private datamedlemmer som beskriver oppdraget.
 */
class Enebolig : public Bolig
{
	int areal;
	bool festetomt;

public:
	Enebolig(int id);				//Konstruktor for manuelt lagde oppdrag
	Enebolig(std::ifstream& inn);	//Konstruktor for lesing fra fil

	void skrivData(std::ostream& ut);
	void skrivTilFil(std::ofstream& ut);
};


#endif