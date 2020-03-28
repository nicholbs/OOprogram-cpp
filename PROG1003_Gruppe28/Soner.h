#pragma once
#include <map>
#include "Sone.h"
#include "Enebolig.h"
using namespace std;

class Soner
{
private:
	int sisteNr = 0;
	map <int, Sone*> soneMap;

public:	
	void nySone(int snr);
	void nyttOppdrag(int snr);
	bool finnesSone(int snr);
	Bolig* finnOppdrag(int onr);
	void skrivOppdrag(int onr);
	void skrivAlleOppdrag();	//TESTFUNKSJON
	void slettOppdrag(int onr);
	void skrivTilFil();
	void lesFraFil();
};