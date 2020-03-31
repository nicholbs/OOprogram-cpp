#ifndef Kunder_H
#define Kunder_H

#pragma once

#include <list>
#include <vector>


class Kunde;

class Kunder
{
    private:
        int sisteNr;        //Konstruktoren initialiserer sisteNr til å bli 0
        std::list<Kunde*> kundeListe;
    public:
        Kunder();

        void nyKunde();
        void kundeEndreData();
        void kunderLesAlleFraFil();
        void kundeSAlleSkrivData();
        void kunderSkrivAlleTilFil();
        void kundeSkrivData();
        bool kundeListeTomSjekk();

        std::vector <int> finnKundeSone(int knrParam);


        void slettKunde();

};

#endif
