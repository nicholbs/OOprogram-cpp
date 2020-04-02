#ifndef __Soner_H
#define __Soner_H
#include <map>
#include <vector>
#include <ostream>
#include "Sone.h"
#include "Enebolig.h"
using namespace std;

/**
 * Klasse Soner er baseklasse, inneholder alle Sone i map.
 */
class Soner
{
private:
	int sisteNr;			//Sist brukte bolig ID
	int antallBoliger;		//Antall boliger some finnes i systemet akkurat nå
	std::map <int, Sone*> soneMap;

public:
	Soner();
	void nySone(int snr);
	void nyttOppdrag(int snr);
	bool finnesSone(int snr);
	Bolig* finnOppdrag(int onr);
	void skrivOppdrag(int onr);
	void skrivAlleOppdragISone(int snr);
	void skrivAlleOppdragISoneTilFil(int snr, std::ostream& ut);
	void skrivHovedDataAlleSoner();		//brukt i case S A for å skrive hovedData om alle Soner
	void slettOppdrag(int onr);
	void skrivTilFil();
	void lesFraFil();
	bool isEmpty();
	std::vector<Bolig*> finnBoligerISone(int snr);
};

#endif