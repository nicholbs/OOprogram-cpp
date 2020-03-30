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
        int sisteNr;        //Konstruktoren initialiserer sisteNr til � bli 0
        list<Kunde*> kundeListe;
    public:
        Kunder();

        void nyKunde();
        void kundeEndreData();
        void kunderLesAlleFraFil();
        void kundeSAlleSkrivData();
        void kunderSkrivAlleTilFil();
        void kundeSkrivData();
        bool kundeListeTomSjekk();

        vector <int> finnKundeSone(int knrParam);


        void slettKunde();

};

#endif