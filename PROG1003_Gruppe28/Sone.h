#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Bolig.h"
using namespace std;

class Sone
{
	int ID;
	string beskrivelse = "";
	vector<Bolig*> boligerTilSalgs;

public:
	Sone(int id);
	void nyttOppdrag(int onr);
	void nyttOppdrag(ifstream& inn);
	Bolig* finnOppdrag(int onr);
	void slettOppdrag(int onr);
	bool finnesOppdrag(int onr);
	void skrivAlleOppdrag(); //TESTFUNKSJON
	void skrivTilFil(ofstream& ut);

};

