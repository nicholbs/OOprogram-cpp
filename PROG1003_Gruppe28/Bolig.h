#pragma once
#include <string>
using namespace std;

enum boligtype{Leilighet, Enebolig};

class Bolig
{
	int ID, dato, bygge�r, bruttoareal, antallSoverom, pris;
	string navnSaksbehandler, navnEier, gateadresse, postadresse, beskrivelse;
	boligtype boligType;
};

