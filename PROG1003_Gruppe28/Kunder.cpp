#include "Kunder.h"
#include "Kunde.h"
#include "LesData3.h"
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;
/**
*Konstruktor som nullstiller dataene
**/
Kunder::Kunder() {
sisteNr = 0;
}

/**
*Denne Funksjonen oppretter lager en ny kundepeker i liste
*
*@param Kunde::Kunde(..)
**/
void Kunder::nyKunde() {
    sisteNr ++; //teller opp sistenr med en
    cout <<("\nNummer er: ") <<sisteNr;
    //Oppretter ny kunde og flytter den bakerst i listen
    kunder.push_back(new Kunde(sisteNr));
}

/**
*Denne funksjonen finner og skriver ut data for alle kunder
*
*@see Kunde::skrivData(..)
**/
void Kunder::kundeSAlleSkrivData(){

}

/**
*Denne Funksjonen finner og skriver ut data til en spesifikk kunde
*
*@see Kunde::kundeIdRetur()
*@see Kunde::skrivData(..)
**/
void Kunder::kundeSkrivData(){
    int nr; //Hvilken kunde skal fa data skrevet ut
    nr = lesInt("\nKundenr: ",1,sisteNr); //hvilken kunde ?
    //Leter etter kunden
    auto it = find_if(kunder.begin(),kunder.end(),
                      [nr](auto val){return(val -> kundeIdRetur() ==nr);});

    //Sa lenge treff pa kunden
    if (it != kunder.end()){
    (*it)-> skrivData();
    }
    else cout <<("\NFinner ikke kunde med id") <<nr;
}


