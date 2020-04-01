#ifndef __Bolig_H
#define __Bolig_H

#include <string>
#include <fstream>
#include "Enum.h"
#include <fstream>
#include <vector>

/**
 * Klasse Bolig er baseklasse for alle Oppdrag lagret i Sone.
 * 
 * Bolig har en rekke privat data som beskriver oppdraget.
 * Det er nevneverdig at Enebolig som er barnet til Bolig arver datamedlemmer som er protected.
 */
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
	Bolig(int id);				//Konstruktor for manuelt lagde oppdrag
	Bolig(std::ifstream& inn);	//Konstruktor for lesing fra fil

	int getID();
	void skrivData(std::ostream& ut);
	void skrivTilFil(std::ofstream& ut);		
	bool erEnebolig();
};

#endif