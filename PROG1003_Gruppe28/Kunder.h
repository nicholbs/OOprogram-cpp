#ifndef Kunder_H
#define Kunder_H

#pragma once

#include <list>
using namespace std;

class Kunde;

class Kunder
{
	int sisteNr;
	list<Kunde*> kunder;
};

#endif
