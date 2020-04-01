#ifndef __Sone_H
#define __Sone_H
#include <string>
#include <vector>
#include <fstream>
#include "Bolig.h"

/**
 * Klasse Sone er underklasse av Soner, Sone blir lagret i Soner.
 *
 * Hver Sone representerer et geografisk område.
 * Sone holder orden på alle Oppdrag i området ved å lagre i vector.
 */
class Sone
{
	int ID;
	std::string beskrivelse = "";
	std::vector<Bolig*> boligerTilSalgs;

public:
	Sone(int id, std::string b);
	void nyttOppdrag(int onr);
	void nyttOppdrag(std::ifstream& inn);
	Bolig* finnOppdrag(int onr);
	void slettOppdrag(int onr);
	bool finnesOppdrag(int onr);
	void skrivAlleOppdrag(); 
	void skrivAlleOppdragTilFil(std::ostream& ut);
	void skrivTilFil(std::ofstream& ut);
	void skrivHovedDataSone();				//brukes av Soner::skrivHovedDataAlleSoner()
	std::vector<Bolig*> getAlleBoliger();

};

#endif