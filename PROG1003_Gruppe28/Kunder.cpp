#include "Kunder.h"
#include "Kunde.h"
#include "LesData3.h"
#include <iostream>
#include <list>
#include <algorithm> //Brukes til en del find funkjoner
#include <iomanip>      //nicholas include pga setw kunder::finnKunder
#include <vector>       //nicholas include pga kunder::finnKunder
#include <fstream> //For innlesning og utlesing til fil

using namespace std;
/**
*Konstruktor som nullstiller dataene
**/
Kunder::Kunder() {
sisteNr = 0;
}

/**
*Denne funksjonen finner en kunde samt endrer
*
*@see Kunde::endreData(..)
**/
void Kunder::kundeEndreData(){
    cin.ignore();
    int nr; //Hvilken kunde skal fa data endrett
    //Kjores kun hvis det finnes kunder
    if(sisteNr !=0){
        nr = lesInt("\nKundenr: ",1,sisteNr); //hvilken kunde ?
        //Leter etter kunden
        auto it = find_if(kundeListe.begin(),kundeListe.end(),
                      [nr](auto val){return(val -> kundeIdRetur() ==nr);});

        //Sa lenge treff, endre kunden.
        if (it != kundeListe.end()){
        (*it)-> endreData();
        }
        else cout << "\n" <<("Finner ikke kunde med id") <<nr;
    }
    else cout <<"\nFATAL Finner ingen kunder";
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
*Denne klassefunkjsonen skriver alle kunder til fil
*
**/
void Kunder::kunderSkrivAlleTilFil(){
    ofstream utfil("KUNDER.DTA");
    //Sa lenge det finnes registrerte kunder:
    if(!kundeListe.empty()){
        utfil << sisteNr <<"\n"; //Legger kunder sistenr pa fil
        for(const auto &val : kundeListe){
            val->skrivTilFil(utfil);
        }
    }else cout <<"\nIngen kunder funnet, Ingenting skrives til fil";



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
*Funksjon for å finne kunde basert på kundenummer parameter
*
* @param int knrParam - variabel for å holde <knr> fra kommando K O <knr>
**/
vector <int>  Kunder::finnKundeSone(int knrParam) {
    vector <int> interesseSone;                 //lager vector for å holde interesse soner til kunden
    for (auto it = kundeListe.begin(); it != kundeListe.end(); it++) //Fra list start til List slutt
        {

            if ((*it)->kundeIdRetur()==knrParam)
                {
                interesseSone = (*it)->kundeSonerRetur();   //interesseSone er lik kunden sin KundeSoner
                return interesseSone;
                }
        }
    cout << setw(35) << "Det er ingen kunder med kunde nr:" << ' ' << knrParam << endl;
    interesseSone.clear();
    return interesseSone;
}

bool Kunder::kundeListeTomSjekk() {
    if (kundeListe.empty() == true)
        return true;
      else if (kundeListe.empty() == false)
          return false;
}



/**Denne klassefunksjonen finner og sletter en spesifikk kunde
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

