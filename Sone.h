#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Bolig.h"


class Sone
{
	int ID;
	std::string beskrivelse = "";
	std::vector<Bolig*> boligerTilSalgs;

public:
	Sone(int id);
	void nyttOppdrag(int onr);
	void nyttOppdrag(std::ifstream& inn);
	Bolig* finnOppdrag(int onr);
	void slettOppdrag(int onr);
	bool finnesOppdrag(int onr);
	void skrivAlleOppdrag(); //TESTFUNKSJON
	void skrivTilFil(std::ofstream& ut);
	void skrivHovedDataSone();				//brukes av Soner::skrivHovedDataAlleSoner()
	std::vector<Bolig*> getAlleBoliger();

};

