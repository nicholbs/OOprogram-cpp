#ifndef __Kunder_H
#define __Kunder_H

#include <list>
#include <vector>


class Kunde;

class Kunder
{
private:
    int sisteNr;        //Konstruktoren initialiserer sisteNr til ? bli 0
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
    void slettKunde();
    std::vector <int> finnKundeSone(int knrParam);
};

#endif
