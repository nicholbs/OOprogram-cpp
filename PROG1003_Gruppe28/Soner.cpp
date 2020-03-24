#include "Soner.h"
#include "Sone.h"
#include <iostream>
#include <iterator>
#include <algorithm>

void Soner::nySone(int snr) {
	Sone* sp = new Sone(snr);
	soneMap.insert(make_pair(snr, sp));
	cout << "Opprettet ny Sone " << snr << "!\n\n";
}

void Soner::nyttOppdrag(int snr) {
	soneMap[snr]->nyttOppdrag(sisteNr + 1);
	sisteNr++;
	cout << "Opprettet ny Bolig " << sisteNr << "!\n\n";
}

bool Soner::finnesSone(int snr) {
	return (soneMap.find(snr) != soneMap.end());
}

const Bolig& Soner::finnOppdrag(int onr) {
	//TODO
}