#include "Sone.h"
#include "Bolig.h"
#include "Enebolig.h"
#include <iostream>
#include <ctype.h>
#include <fstream>			//nicholas lagt til for skrivTilFil

using namespace std;

Sone::Sone(int id) {
	ID = id;
}

void Sone::nyttOppdrag(int onr)
{
	cout << "Leilighet/enebolig [L/E]: ";
	char valg; cin >> valg;

	Bolig* p = nullptr;
	if (toupper(valg) == 'L')
		p = new Bolig(onr);
	else if (toupper(valg) == 'E')
		p = new Enebolig(onr);

	boligerTilSalgs.push_back(p);
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
	cout << '\n';
}

//void Sone::skrivTilFil() {
//	ofstream utfilA("Kxxxxx.TXT");
//	auto it = boligerTilSalgs.begin();
//	(*it)->skrivTilFil(utfilA);
//}