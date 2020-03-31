#include "Sone.h"
#include "Bolig.h"
#include "Enebolig.h"
#include <iostream>
#include <ctype.h>			//nicholas lagt til for skrivTilFil
#include <iomanip>

using namespace std;

/**
 * Sone er parameterfult konstruktor som initialiserer Sone sin ID til aa vaere medsendt param.
 *
 * @Param int id - ID til Sone
 */
Sone::Sone(int id) {
	ID = id;
}

/**
 * nyttOppdrag oppretter ny Oppdrag basert på input og medsendt param, legger til Oppdrag i Sone.
 *
 * @Param int onr - ID til Oppdrag
 */
void Sone::nyttOppdrag(int onr)
{
	cout << "Leilighet/enebolig [L/E]: ";
	char valg; cin >> valg;

	Bolig* bp = nullptr;
	if (toupper(valg) == 'L')
		bp = new Bolig(onr);
	else if (toupper(valg) == 'E')
		bp = new Enebolig(onr);

	boligerTilSalgs.push_back(bp);
}

/**
 * nyttOppdrag oppretter ny Oppdrag basert på input fra medsendt fil, legger til Oppdrag i Sone.
 *
 * Leser BoligType fra fil
 * Oppretter ny Oppdrag basert på BoligType 
 * Legger til Oppdrag i Sone
 * 
 * @Param int onr - ID til Oppdrag
 * @See Bolig::Bolig(ifstream& inn)
 */
void Sone::nyttOppdrag(ifstream& inn)
{
	Bolig* bp = nullptr;

	char lestChar;
	inn >> lestChar;
	
	if (lestChar == 'L')
		bp = new Bolig(inn);
	else
		bp = new Enebolig(inn);

	boligerTilSalgs.push_back(bp);
}

Bolig* Sone::finnOppdrag(int onr) 
{
	for (unsigned int i = 0; i < boligerTilSalgs.size(); i++) 
	{
		if (boligerTilSalgs[i]->getID() == onr)
			return boligerTilSalgs[i];
	}
	return nullptr;
}

void Sone::slettOppdrag(int onr)
{
	for (unsigned int i = 0; i < boligerTilSalgs.size(); i++)
	{
		if (boligerTilSalgs[i]->getID() == onr)
		{
			delete boligerTilSalgs[i];
			boligerTilSalgs.erase(boligerTilSalgs.begin() + i);
		}
	}
}

bool Sone::finnesOppdrag(int onr)
{
	for (unsigned int i = 0; i < boligerTilSalgs.size(); i++)
	{
		if (boligerTilSalgs[i]->getID() == onr)
			return true;
	}
	return false;
}

void Sone::skrivAlleOppdrag()
{
	cout << "\nSone " << ID;
	for (unsigned int i = 0; i < boligerTilSalgs.size(); i++)
		cout << "\nBolig " << boligerTilSalgs[i]->getID();
	cout << "\n\n";
}

void Sone::skrivTilFil(ofstream& ut) {
	ut << ID << " " << boligerTilSalgs.size() << '\n';
	for (int i = 0; i < boligerTilSalgs.size(); i++)
	{
		if (boligerTilSalgs[i]->erEnebolig())
			static_cast<Enebolig*>(boligerTilSalgs[i])->skrivTilFil(ut);
		else 
			boligerTilSalgs[i]->skrivTilFil(ut);
	}
}

/**
 *   Funksjon for å skrive ut hoved data om hver Sone i Soner
 *
 *	 Brukes av Soner::skrivHovedDataAlleSoner() ved foor loop.
 *   HovedData for hver sone er dens ID, beskrivelse og antall boliger i sonen.
 */
void Sone::skrivHovedDataSone() {
	cout << setw(35) << "Skriver hoveddata om sone" << ' ' << ID << endl;
	
	cout << setw(35) << "Beskrivelse av sonen:" << ' ' << beskrivelse << endl;
	cout << setw(35) << "Antall boliger til salgs i sonen" << ' ' << boligerTilSalgs.size() << endl << endl;
}

vector<Bolig*> Sone::getAlleBoliger()
{
	return boligerTilSalgs;
}
