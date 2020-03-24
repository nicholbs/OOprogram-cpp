#pragma once
#include <map>
#include "Sone.h"
#include "Bolig.h"
using namespace std;

class Soner
{
private:
	int sisteNr;
	map <int, Sone*> soneMap;

public:	
	void nySone(int snr);
	void nyttOppdrag(int snr);
	bool finnesSone(int snr);
	Bolig* finnOppdrag(int onr);
	void skrivOppdrag(int onr);
};