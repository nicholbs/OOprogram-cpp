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

/**
 * finnOppdrag leter etter Oppdrag med ID fra param, returnerer enten peker til Oppdraget eller nullptr.
 *
 * Går gjennom alle Oppdrag i Sone.
 * Sjekker ID med int onr parameter.
 * Dersom funnet returnerer peker til Oppdrag, dersom ikke nullptr.
 *
 * @Param int onr - ID til Oppdrag
 * @Return nullptr/boligerTilSalgs[i] - Enten peker til Oppdrag eller nullptr
 */
Bolig* Sone::finnOppdrag(int onr) 
{
	for (unsigned int i = 0; i < boligerTilSalgs.size(); i++) 
	{
		if (boligerTilSalgs[i]->getID() == onr)
			return boligerTilSalgs[i];
	}
	return nullptr;
}

/**
 * slettOppdrag leter etter Oppdrag med ID fra param, dersom funnet sletter Oppdrag og fjerner peker.
 *
 * Går gjennom alle Oppdrag i Sone.
 * Bruker getID for å sjekke ID med int onr parameter.
 * Dersom funnet sletter Oppdrag og fjerner peker i boligerTilSalgs.
 *
 * @Param int onr - ID til Oppdrag
 * @See Bolig::getID()
 */
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

/**
 * finnesOppdrag leter etter Oppdrag med ID fra param, returnerer true/false
 *
 * Går gjennom alle Oppdrag i Sone.
 * Bruker getID for å sjekke ID med int onr parameter.
 * Returnerer true/false basert på resultat av sjekk.
 *
 * @Param int onr - ID til Oppdrag
 * @See Bolig::getID()
 * @Return bool statement - true/false
 */
bool Sone::finnesOppdrag(int onr)
{
	for (unsigned int i = 0; i < boligerTilSalgs.size(); i++)
	{
		if (boligerTilSalgs[i]->getID() == onr)
			return true;
	}
	return false;
}

/**
 * skrivAlleOppdrag skriver ut Sone sin ID og antall Oppdrag i Sone.
 *
 * Går gjennom alle Oppdrag i Sone.
 * Bruker getID for å hente ID til Oppdrag.
 *
 * @See Bolig::getID()
 */
void Sone::skrivAlleOppdrag()
{
	cout << "\nSone " << ID;
	for (unsigned int i = 0; i < boligerTilSalgs.size(); i++)
		cout << "\nBolig " << boligerTilSalgs[i]->getID();
	cout << "\n\n";
}

/**
 * skrivTilFil går gjennom alle Oppdrag i Sone og bruker Oppdrag sin skrivTilFil.
 *
 * Går gjennom alle Oppdrag i Sone.
 * Sjekker Oppdrag type.
 * Bruker Oppdraget sin skrivTilFil med param.
 * 
 * @Param ofstream& ut - utfill medsendt, blir til "SONER.DTA"
 * @See Bolig::erEnebolig()
 * @See Enebolig::skrivTilFIl()
 * @See Bolig::skrivTilFil()
 */
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

/**
 *   getAlleBoliger returnerer alle Boliger fra Sone.
 *
 * @Return vector <Bolig*> boligerTilSalgs - Alle boliger i Sone
 */
vector<Bolig*> Sone::getAlleBoliger()
{
	return boligerTilSalgs;
}
