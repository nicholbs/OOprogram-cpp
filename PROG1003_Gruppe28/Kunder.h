#ifndef Kunder_H
#define Kunder_H

#pragma once

#include <list>
using namespace std;

class Kunde;

class Kunder
{
    private:
        int sisteNr;
        list<Kunde*> kundeListe;
    public:
        Kunder();
        Kunde* finnKunde(); //Ikke i bruk
        void nyKunde();
        void kundeSAlleSkrivData();
        void kundeSkrivData();
        void slettKunde();
};

#endif
