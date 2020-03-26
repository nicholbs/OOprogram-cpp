#ifndef Kunder_H
#define Kunder_H

#pragma once

#include <list>
#include <vector>
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
        void kundeEndreData();
        void kundeSAlleSkrivData();
        void kundeSkrivData();

        vector <int> finnKunde(int knrParam);
       

        void slettKunde();

};

#endif
