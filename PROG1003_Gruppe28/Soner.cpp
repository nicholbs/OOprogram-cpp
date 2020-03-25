#include "Soner.h"
#include "Sone.h"
#include <iostream>
#include <iterator>
#include <algorithm>

void Soner::nySone(int snr) 
{
	Sone* sp = new Sone(snr);
	soneMap.insert(make_pair(snr, sp));
	cout << "Opprettet ny Sone " << snr << "!\n\n";
}

void Soner::nyttOppdrag(int snr) 
{
	const auto& so = soneMap.find(snr);
	if (so != soneMap.end()) 
	{
		so->second->nyttOppdrag(sisteNr + 1);
		sisteNr++;
		cout << "Opprettet ny Bolig " << sisteNr << "!\n\n";
	}
	else 
	{
		cout << "Fant ingen Sone " << snr << ".\n\n";
	}
}

bool Soner::finnesSone(int snr) 
{
	return (soneMap.find(snr) != soneMap.end());
}

Bolig* Soner::finnOppdrag(int onr) 
{
	Bolig* bp = nullptr;
	for (const auto& sonePar : soneMap) 
	{
		bp = sonePar.second->finnOppdrag(onr);
		if (bp != nullptr)
			return bp;
	}
	cout << "Fant ikke oppdraget.\n\n";
	return bp;
}

void Soner::skrivOppdrag(int onr) 
{
	Bolig* bp = finnOppdrag(onr);
	if(bp != nullptr)
		bp->skrivData();
}

void Soner::skrivAlleOppdrag()
{
	for (const auto& sonePar : soneMap)
		sonePar.second->skrivAlleOppdrag();
}

void Soner::slettOppdrag(int onr)
{
	for (const auto& sonePar : soneMap)
	{
		if (sonePar.second->finnesOppdrag(onr))
			sonePar.second->slettOppdrag(onr);
	}
}