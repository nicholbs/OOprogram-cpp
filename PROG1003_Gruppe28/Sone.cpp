#include "Sone.h"
#include "Bolig.h"
#include "Enebolig.h"
#include <iostream>
#include <ctype.h>

using namespace std;

Sone::Sone(int id) {
	ID = id;
}

void Sone::nyttOppdrag(int onr)
{
	cout << "Leilighet/enebolig [L/E]: ";
	char valg; cin >> valg;

	Bolig* p = nullptr;
	if (toupper(valg) == 'L')
		p = new Bolig(onr);
	else if (toupper(valg) == 'E')
		p = new Enebolig(onr);

	boligerTilSalgs.push_back(p);
}
