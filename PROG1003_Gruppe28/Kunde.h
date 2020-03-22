#pragma once

#include <vector>
#include <string>

using namespace std;

enum boligtype {Leilighet, Bolig};

class Kunde
{
	int ID, telefon;
	string navn, gateAddresse, postAdresse, mail;
	boligtype boligType;
	vector<int> soner;
};

