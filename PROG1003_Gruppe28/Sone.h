#pragma once
#include <string>
#include <vector>
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
	Bolig* finnOppdrag(int onr);
};

