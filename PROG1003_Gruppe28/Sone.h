#pragma once
#include <string>
#include <vector>
using namespace std;

class Bolig;
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

