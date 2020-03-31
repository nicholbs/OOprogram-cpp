#include "Soner.h"
#include "Sone.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iomanip>

/**
 * Dette er parameterlos konstruktor for Soner, initialiserer siteNr til � bli 0
 * */
Soner::Soner()
{
	sisteNr = 0;
}

/**
 * nySone er funksjon for � lage nye "Sone" objekter i Soner sin map.
 *
 * Sjekker om sonen finnes allerede ved hjelp av parameter og finnesSone().
 * Lager ny Sone og legger den til i Soner sin map.
 *
 * @See Soner::finnesSone 
 * @Param int snr
 * */
void Soner::nySone(int snr) 
{
	if (finnesSone(snr))
		cout << "Sone " << snr << " finnes allerede!\n";
	else
	{
		Sone* sp = new Sone(snr);
		soneMap.insert(make_pair(snr, sp));
		skrivTilFil();
		cout << "Opprettet ny Sone " << snr << "!\n\n";
	}
}

/**
 * nyttOppdrag leter etter sone og oppretter nytt oppdrag dersom funnet.
 *
 * 
 *	
 *
 *
 * @Param int snr
 * @See Sone::nyttOppdrag()
 * @See Soner::skrivTilFil()
 * */
void Soner::nyttOppdrag(int snr) 
{
	const auto& so = soneMap.find(snr);
	if (so != soneMap.end()) 
	{
		so->second->nyttOppdrag(sisteNr + 1);
		sisteNr++;
		skrivTilFil();
		cout << "Opprettet ny Bolig " << sisteNr << "!\n\n";
	}
	else 
	{
		cout << "Fant ingen Sone " << snr << ".\n\n";
	}
}

void Soner::slettOppdrag(int onr)
{
	for (const auto& sonePar : soneMap)
	{
		if (sonePar.second->finnesOppdrag(onr))
		{
			sonePar.second->slettOppdrag(onr);
			sisteNr--;
			skrivTilFil();
			return;
		}
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
	cout << setw(35) << "Fant ikke oppdraget.\n\n";
	return bp;
}

void Soner::skrivOppdrag(int onr) 
{
	Bolig* bp = finnOppdrag(onr);
	if (bp != nullptr)
	{
		if (bp->erEnebolig())
			static_cast<Enebolig*>(bp)->skrivData();
		else
			bp->skrivData();
	}
}

void Soner::skrivAlleOppdrag()
{
	for (const auto& sonePar : soneMap)
		sonePar.second->skrivAlleOppdrag();
}

void Soner::skrivTilFil()
{
	ofstream ut;
	ut.open("SONER.DTA");

	ut << soneMap.size() << '\n';
	for (const auto& sonePar : soneMap)
		sonePar.second->skrivTilFil(ut);

	ut.close();
}

void Soner::lesFraFil()
{
	ifstream inn;
	inn.open("SONER.DTA");

	int soneNr, antallOppdrag, antallSoner;

	if (!inn)
		cout << setw(35) << "Kunne ikke lese fil \"SONER.DTA\"\n\n";
	else
	{
		inn >> antallSoner;
		for (int i = 0; i < antallSoner; i++)
		{
			inn >> soneNr >> antallOppdrag;
			inn.ignore();

			Sone* sp = new Sone(soneNr);
			for (int i = 0; i < antallOppdrag; i++)
				sp->nyttOppdrag(inn);
			soneMap.insert(make_pair(soneNr, sp));
		}
	}
}

bool Soner::isEmpty() {
	return soneMap.empty();
}

/**
*   G�r gjennom alle instanser i Soner sin map av type Sone pekere og skriver Sone sin hovedData.
*
*   sonePar er for range basert gjennomgang av Soner sin map. For hver instant bruker vi
*	valgt Sone sin skrivHovedDataSone funksjon
*
*   @see     Sone::skrivHovedDataSone()
*/
void Soner::skrivHovedDataAlleSoner() {
	cout << setw(35) << "Skriver ut alle hoved data om soner:" << endl;
	for (const auto& sonePar : soneMap)
		{
		sonePar.second->skrivHovedDataSone();
		}
}