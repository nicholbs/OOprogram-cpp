#pragma once
#include <map>
#include <vector>
#include "Sone.h"
#include "Enebolig.h"
using namespace std;

class Soner
{
private:
	int sisteNr = 0;
	std::map <int, Sone*> soneMap;

public:
	Soner();
	void nySone(int snr);
	void nyttOppdrag(int snr);
	bool finnesSone(int snr);
	Bolig* finnOppdrag(int onr);
	void skrivOppdrag(int onr);
	void skrivAlleOppdrag();	//TESTFUNKSJON
	void skrivHovedDataAlleSoner();		//brukt i case S A for å skrive hovedData om alle Soner
	void slettOppdrag(int onr);
	void skrivTilFil();
	void lesFraFil();
	bool isEmpty();
	std::vector<Bolig*> finnBoligerISone(int snr);
};
