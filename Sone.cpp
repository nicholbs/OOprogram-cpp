#include "Sone.h"
#include "Bolig.h"
#include "Enebolig.h"
#include <iostream>
#include <ctype.h>			//nicholas lagt til for skrivTilFil
#include <iomanip>
#include "LesData3.h"

using namespace std;

/**
 * Sone er parameterfult konstruktor som initialiserer Sone sin ID til aa vaere medsendt param.
 *
 * @Param int id - ID til Sone
 */
Sone::Sone(int id, string b) {
	ID = id;
    beskrivelse = b;
}

/**
 * nyttOppdrag oppretter ny Oppdrag basert p? input og medsendt param, legger til Oppdrag i Sone.
 *
 * @Param int onr - ID til Oppdrag
 */
void Sone::nyttOppdrag(int onr)
{
    char valg;
    do {
        valg = lesChar("Leilighet/enebolig [L/E]");
    } while (valg != 'E' && valg != 'L');
	

	Bolig* bp = nullptr;
	if (toupper(valg) == 'L')
		bp = new Bolig(onr);
	else if (toupper(valg) == 'E')
		bp = new Enebolig(onr);

	boligerTilSalgs.push_back(bp);
}

/**
 * nyttOppdrag oppretter ny Oppdrag basert p? input fra medsendt fil, legger til Oppdrag i Sone.
 *
 * Leser BoligType fra fil
 * Oppretter ny Oppdrag basert p? BoligType 
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
 * G?r gjennom alle Oppdrag i Sone.
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
 * G?r gjennom alle Oppdrag i Sone.
 * Bruker getID for ? sjekke ID med int onr parameter.
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
 * G?r gjennom alle Oppdrag i Sone.
 * Bruker getID for ? sjekke ID med int onr parameter.
 * Returnerer true/false basert p? resultat av sjekk.
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
 * G?r gjennom alle Oppdrag i Sone.
 * Bruker getID for ? hente ID til Oppdrag.
 *
 * @See Bolig::getID()
 */
void Sone::skrivAlleOppdrag()
{
    if (boligerTilSalgs.empty())
    {
        cout << "\nSone " << ID << " har ingen oppdrag.\n";
    }
    else
    {
        cout << "\n SONE " << ID << "\n\"" << beskrivelse << "\""
           << "\n-----------------------------------------------------\n";
        for (int i = 0; i < boligerTilSalgs.size(); i++)
        {
            if (boligerTilSalgs[i]->erEnebolig())
                static_cast<Enebolig*>(boligerTilSalgs[i])->skrivData(cout);
            else
                boligerTilSalgs[i]->skrivData(cout);
            cout << "\n-----------------------------------------------------\n";

            if ((i + 1) % 5 == 0 && i != 0)
            {
                cout << '\n';
                system("pause");
                cout << "\n-----------------------------------------------------\n";
            }
                
        }
    }
}

void Sone::skrivAlleOppdragTilFil(ostream& ut)
{
    if (!boligerTilSalgs.empty())
    {
        ut << "\n SONE " << ID << "\n\"" << beskrivelse << "\""
            << "\n-----------------------------------------------------\n";
        for (int i = 0; i < boligerTilSalgs.size(); i++)
        {
            if (boligerTilSalgs[i]->erEnebolig())
                static_cast<Enebolig*>(boligerTilSalgs[i])->skrivData(ut);
            else
                boligerTilSalgs[i]->skrivData(ut);
            ut << "\n-----------------------------------------------------\n";
        }
    }
}

/**
 * skrivTilFil g?r gjennom alle Oppdrag i Sone og bruker Oppdrag sin skrivTilFil.
 *
 * G?r gjennom alle Oppdrag i Sone.
 * Sjekker Oppdrag type.
 * Bruker Oppdraget sin skrivTilFil med param.
 * 
 * @Param ofstream& ut - utfill medsendt, blir til "SONER.DTA"
 * @See Bolig::erEnebolig()
 * @See Enebolig::skrivTilFIl()
 * @See Bolig::skrivTilFil()
 */
void Sone::skrivTilFil(ofstream& ut) {
    ut  << ID << " " << boligerTilSalgs.size() << '\n'
        << beskrivelse << '\n';
	for (int i = 0; i < boligerTilSalgs.size(); i++)
	{
		if (boligerTilSalgs[i]->erEnebolig())
			static_cast<Enebolig*>(boligerTilSalgs[i])->skrivTilFil(ut);
		else 
			boligerTilSalgs[i]->skrivTilFil(ut);
	}
}

/**
 *   Funksjon for ? skrive ut hoved data om hver Sone i Soner
 *
 *	 Brukes av Soner::skrivHovedDataAlleSoner() ved foor loop.
 *   HovedData for hver sone er dens ID, beskrivelse og antall boliger i sonen.
 */
void Sone::skrivHovedDataSone() {
    cout << " SONE " << ID
        << "\nBoliger: " << boligerTilSalgs.size()
        << "\n\"" << beskrivelse << "\"\n";
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
