#pragma once
#include <string>
using namespace std;

enum boligtype{Leilighet, Enebolig};

class Bolig
{
	int ID, dato, byggeår, bruttoareal, antallSoverom, pris;
	string navnSaksbehandler, navnEier, gateadresse, postadresse, beskrivelse;
	boligtype boligType;
};

