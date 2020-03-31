#include "Soner.h"
#include "Sone.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iomanip>

/**
 * Dette er parameterlos konstruktor for Soner, initialiserer siteNr til � bli 0
 **/
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
 **/
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
 * Leter etter Sone med parameter som nr.
 * Dersom Sone eksisterer opprettes ny bolig.
 * Bolig skriver s� til Soner.DTA
 *
 * @Param int snr
 * @See Sone::nyttOppdrag()
 * @See Soner::skrivTilFil()
 **/
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

/**
 * slettOppdrag leter etter oppdrag og sletter dersom funnet.
 *
 * G�r gjennom hele map og bruker finnesOppdrag() med parameter for � lete etter oppdrag
 * Dersom oppdrag er funnet brukes slettOppdrag() og sisteNr blir redusert.
 * Til slutt skrives filen Soner.DTA p� nytt.
 *
 * @Param int onr
 * @See Sone::finnesOppdrag()
 * @See Sone::slettOppdrag()
 * @See Soner::skrivTilFil()
 **/
void Soner::slettOppdrag(int onr)
{
	for (const auto& sonePar : soneMap)
	{
		if (sonePar.second->finnesOppdrag(onr))
		{
			sonePar.second->slettOppdrag(onr);
			sisteNr--;
			skrivTilFil();
			return;			//Stopper � loope i map dersom oppdraget ble funnet
		}
	}
}

/**
 * finnesSone leter etter Sone, returnerer true/false basert p� resultat.
 *
 * Leter etter Sone med parameter som nr.
 * Dersom Sone eksisterer returneres true/false.
 *
 * @Param int snr
 * @Return bool statement
 **/
bool Soner::finnesSone(int snr) 
{
	return (soneMap.find(snr) != soneMap.end());
}


/**
 * finnOppdrag tar parameter, leter etter oppdraget, returnerer peker dersom funnet.
 *
 * Leter etter Oppdrag med parameter som nr.
 * Bruker Sone::finnOppdrag til � finne oppdraget. 
 * Dersom Oppdrag eksisterer returneres peker til Oppdraget.
 *
 * @See Sone::finnOppdrag()
 * @Param int snr
 * @Return bp - Bolig peker
 **/
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

/**
 * skrivOppdrag leter etter oppdraget, skriver ut dersom funnet og basert p� type oppdrag.
 *
 * Leter etter Oppdrag med parameter som nr.
 * Bruker Soner::finnOppdrag til � finne oppdraget.
 * Dersom Oppdrag eksisterer, bruk den sin skrivData().
 *
 * @See Soner::finnOppdrag()
 * @See Bolig::erEnebolig()
 * @See Bolig::skrivData()
 * @See Enebolig::skrivData()
 * @Param int onr
 **/
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

/**
 * skrivAlleOppdrag g�r gjennom alle Sone i Soner, skriver ut alle oppdrag i Sonene.
 *
 * Range basert gjennom hele Soner sin vector
 *	
 * @See Sone::skrivAlleOppdrag()
 **/
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

vector<Bolig*> Soner::finnBoligerISone(int snr)
{
	return (soneMap.at(snr)->getAlleBoliger());
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