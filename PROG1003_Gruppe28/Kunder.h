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
        void nyKunde();
        void kundeSAlleSkrivData();
        void kundeSkrivData();
        void finnKunde(int knrParam);
};

#endif
