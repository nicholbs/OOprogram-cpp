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
*Denne funksjonen finner en kunde i listen og returnerer denne
*
*@return    Kunde*  Returnerer en peker til en kunde, hvis ingen treff nullptr
**/
Kunde* Kunder::finnKunde(){
/*
    int nr;
    //Leter igjennom listen
    iterator it = find_if(kundeListe.begin(),kundeListe.end(),
                      [nr](auto val){return(val -> kundeIdRetur() ==nr);});


**/

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
    kundeListe.push_back(new Kunde(sisteNr));
}

/**
*Denne funksjonen finner og skriver ut data for alle kunder
*
*@see Kunde::skrivData(..)
**/
void Kunder::kundeSAlleSkrivData(){
    int teller = 0; //hjelpeint for a stoppe pr 10 utskrift av kunde
    //Skriver ut alle kunder ifra listen
    for(const auto & liste :kundeListe) {
        teller ++;
        //Pauser for hvert 10 kunde
        if(teller%10==0){
            cin.ignore(); //Far bruker a taste enter
        }
        liste -> skrivData(); //Kaller pa kunde lesdata
        cout <<"\n";
    }
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
    auto it = find_if(kundeListe.begin(),kundeListe.end(),
                      [nr](auto val){return(val -> kundeIdRetur() ==nr);});

    //Sa lenge treff pa kunden sa skriver jeg ut data
    if (it != kundeListe.end()){
    (*it)-> skrivData();
    }
    else cout << '\n' <<("Finner ikke kunde med id") <<nr;
}

/**
*Denne klassefunksjonen finner og sletter en spesifikk kunde
*
*@see Kunde::kundeIdReturn()
**/
void Kunder::slettKunde() {
     int nr;
     cout <<"\nHvilken kunde vil du slette? ";
     cin >> nr;
     //leter etter kunden
     auto it = find_if(kundeListe.begin(),kundeListe.end(),
                      [nr](auto val){return(val -> kundeIdRetur() ==nr);});

   //Sa lenge den finnes
    if(it !=kundeListe.end()){
        delete (*it); //Sletter brukerobjektet
        kundeListe.remove((*it)); //Fjerner peker fra listen
        cout <<"\nBruker er slettet";
    }
    else cout <<"\nFATAL finner ikke bruker, slett ikke mulig";

}


