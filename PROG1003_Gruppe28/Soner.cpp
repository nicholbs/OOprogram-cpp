#include "Soner.h"
#include "Sone.h"
#include <iostream>

void Soner::nySone(int snr)
{
	Sone* sp = new Sone(snr);
	soneMap.insert(make_pair(snr, sp));
	cout << "Opprettet ny Sone " << snr << "!\n\n";
}

void Soner::nyBolig(int snr)
{
	soneMap[snr]->nyBolig(sisteNr + 1);
	//Finnes Bolig (sisteNr + 1)?
	sisteNr++;
	cout << "Opprettet ny Bolig " << sisteNr << "!\n\n";
}
