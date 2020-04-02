#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "Soner.h"
#include "Sone.h"
#include "LesData3.h"
#include "Const.h"

/**
 * Dette er parameterlos konstruktor for Soner, initialiserer siteNr til å bli 0
 **/
Soner::Soner()
{
	sisteNr = 0;
    antallBoliger = 0;
}

/**
 * nySone er funksjon for å lage nye "Sone" objekter i Soner sin map.
 *
 * Sjekker om sonen finnes allerede ved hjelp av parameter og finnesSone().
 * Lager ny Sone og legger den til i Soner sin map.
 *
 * @See Soner::finnesSone(..) 
 * @Param int snr - Sonen sitt nr
 **/
void Soner::nySone(int snr) 
{
	if (finnesSone(snr))
		cout << "Sone " << snr << " finnes allerede!\n";
	else
	{
        string beskrivelse;
        cout << "\nBeskrivelse: ";
        getline(cin, beskrivelse);

		Sone* sp = new Sone(snr, beskrivelse);
		soneMap.insert(make_pair(snr, sp));
		cout << "Opprettet ny Sone " << snr << "!\n\n";
	}
}

/**
 * nyttOppdrag leter etter sone og oppretter nytt oppdrag dersom funnet.
 *
 * Leter etter Sone med parameter som nr.
 * Dersom Sone eksisterer opprettes ny bolig.
 * Bolig skriver så til Soner.DTA
 *
 * @Param int snr - Sonen sitt nr
 * @See Sone::nyttOppdrag()
 * @See Soner::skrivTilFil()
 **/
void Soner::nyttOppdrag(int snr) 
{
    if (antallBoliger < MAX_OPPDRAG)
    {
        const auto& so = soneMap.find(snr);
        if (so != soneMap.end())
        {
            so->second->nyttOppdrag(sisteNr + 1);
            sisteNr++;
            antallBoliger++;
            cout << "Opprettet ny Bolig " << sisteNr << "!\n";
        }
        else
            cout << "Fant ingen Sone " << snr << ".\n";
    }
    else
        cout << "\nSystemet kan ikke ha mer enn " << MAX_OPPDRAG << " oppdrag.\n";
}

/**
 * slettOppdrag leter etter oppdrag og sletter dersom funnet.
 *
 * Går gjennom hele map og bruker finnesOppdrag() med parameter for å lete etter oppdrag
 * Dersom oppdrag er funnet brukes slettOppdrag() og sisteNr blir redusert.
 * Til slutt skrives filen Soner.DTA på nytt.
 *
 * @Param int onr - Oppdraget sitt nr
 * @See Sone::finnesOppdrag()
 * @See Sone::slettOppdrag()
 * @See Soner::skrivTilFil()
 **/
void Soner::slettOppdrag(int onr)
{
    char konfirmasjon;

    for (const auto& sonePar : soneMap)
    {
        if (sonePar.second->finnesOppdrag(onr))
        {
            konfirmasjon = lesChar("\nNB! Hvis du sletter et Oppdrag er det borte for alltid. Slett? [j/n]");
            if (konfirmasjon == 'J')
            {
                sonePar.second->slettOppdrag(onr);
                antallBoliger--;
                cout << "Oppdrag " << onr << " har blitt slettet.\n";		
            }
            else
            {
                cout << "Oppdraget ble ikke slettet.\n";
            }
            return;     //Stopper å loope i map dersom oppdraget ble funnet
        }
    }   
}

/**
 * finnesSone leter etter Sone, returnerer true/false basert på resultat.
 *
 * Leter etter Sone med parameter som nr.
 * Dersom Sone eksisterer returneres true/false.
 *
 * @Param int snr - Sonen sitt nr
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
 * Bruker Sone::finnOppdrag til å finne oppdraget. 
 * Dersom Oppdrag eksisterer returneres peker til Oppdraget.
 *
 * @See Sone::finnOppdrag()
 * @Param int snr - Sonen sitt nr
 * @Return bp - peker til Oppdraget
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
 * skrivOppdrag leter etter oppdraget, skriver ut dersom funnet og basert på type oppdrag.
 *
 * Leter etter Oppdrag med parameter som nr.
 * Bruker Soner::finnOppdrag til å finne oppdraget.
 * Dersom Oppdrag eksisterer, bruk den sin skrivData().
 *
 * @See Soner::finnOppdrag()
 * @See Bolig::erEnebolig()
 * @See Bolig::skrivData()
 * @See Enebolig::skrivData()
 * @Param int onr - Oppdrag sitt nr
 **/
void Soner::skrivOppdrag(int onr) 
{
	Bolig* bp = finnOppdrag(onr);
	if (bp != nullptr)
	{
        cout << "\n-----------------------------------------------------\n";
		if (bp->erEnebolig())
			static_cast<Enebolig*>(bp)->skrivData(cout);
		else
			bp->skrivData(cout);
        cout << "\n-----------------------------------------------------\n";
	}
}

/**
 *  Skriver alle oppdrag i én sone til terminalen.
 *
 * @See Sone::skrivAlleOppdrag(..)
 **/
void Soner::skrivAlleOppdragISone(int snr)
{
    soneMap.at(snr)->skrivAlleOppdrag();
}

/**
 *  Skriver alle oppdrag i én sone til leselig fil.
 *
 * @See Sone::skrivAlleOppdragTilFil(..)
 **/
void Soner::skrivAlleOppdragISoneTilFil(int snr, std::ostream& ut)
{
    soneMap.at(snr)->skrivAlleOppdragTilFil(ut);
}

/**
 * skrivTilFil lager "SONER.DTA" fil, skriver til fil antall Sone i Soner, skriver til fil oppdrag i Sone.
 *
 * Range basert gjennom hele Soner sin Map.
 * Bruker tilpekt sone sin skrivTilFil for å skrive oppdrag i sone til fil.
 *
 * @See Sone::skrivTilFil()
 **/
void Soner::skrivTilFil()
{
	ofstream ut;
	ut.open("SONER.DTA");

	ut << soneMap.size() << '\n';
	for (const auto& sonePar : soneMap)
		sonePar.second->skrivTilFil(ut);

	ut.close();
}

/**
 * lesFraFil åpner "SONER.DTA" fil, lager og leser inn nye Sone + oppdrag, legger til Sone i Soner.
 *
 * Dersom "SONER.DTA" finnes leses antall sone.
 * Går gjennom alle sone i fil, lager og leser inn Sone pluss den sine oppdrag.
 * Legger til Sone i Soner sin map.
 *
 * @See Sone::nyttOppdrag()
 **/
void Soner::lesFraFil()
{
	ifstream inn;
	inn.open("SONER.DTA");

	int soneNr, antallOppdrag, antallSoner;
    string soneBeskrivelse;

	if (!inn)
		cout << setw(35) << "Kunne ikke lese fil \"SONER.DTA\"\n\n";
	else
	{
		inn >> antallSoner;
		for (int i = 0; i < antallSoner; i++)
		{
			inn >> soneNr >> antallOppdrag;
			inn.ignore();
            getline(inn, soneBeskrivelse);

			Sone* sp = new Sone(soneNr, soneBeskrivelse);
			for (int i = 0; i < antallOppdrag; i++)
				sp->nyttOppdrag(inn);
			soneMap.insert(make_pair(soneNr, sp));
		}
	}
}

/**
 * isEmpty sjekker om det finnes Sone i Soner sin map, returnerer true/false.
 **/
bool Soner::isEmpty() {
	return soneMap.empty();
}

/**
 * finnBoligerISone finner Sone med parameter, henter alle boliger fra Sone i vector.
 *
 * @See Sone::getAlleBoliger()
 * @Param int snr - Sonen sitt nr
 * @Return vector<Bolig*> boligerTilSalgs - vector fra Sonen
 **/
vector<Bolig*> Soner::finnBoligerISone(int snr)
{
	return soneMap.at(snr)->getAlleBoliger();
}

/**
 *   Går gjennom alle instanser i Soner sin map av type Sone pekere og skriver Sone sin hovedData.
 *
 *   sonePar er for range basert gjennomgang av Soner sin map. For hver instant bruker vi
 *	valgt Sone sin skrivHovedDataSone funksjon
 *
 *   @see     Sone::skrivHovedDataSone()
 */
void Soner::skrivHovedDataAlleSoner() {
    if (!soneMap.empty())
    {
        cout << "\n-----------------------------------------------------\n";
        for (const auto& sonePar : soneMap)
        {
            sonePar.second->skrivHovedDataSone();
            cout << "-----------------------------------------------------\n";
        }
    }
    else
        cout << "\nDet finnes ingen soner i systemet.\n";
}