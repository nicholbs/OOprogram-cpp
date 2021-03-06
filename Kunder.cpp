#include "Const.h"
#include "Funksjoner.h"
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
    int nr; //Hvilken kunde skal fa data endrett
    nr = lesIntX(1, MAX_PERSONER);
    if (nr != 0)
    {
        //Kjores kun hvis det finnes kunder
        if (!kundeListe.empty())
        {
            //Leter etter kunden
            auto it = find_if(kundeListe.begin(), kundeListe.end(),
                [nr](auto val) {return(val->kundeIdRetur() == nr); });

            //Sa lenge treff, endre kunden.
            if (it != kundeListe.end())
                (*it)->endreData();
            else
                cout << "\n" << ("Finner ikke kunde med ID ") << nr;
        }
        else cout << "\nIngen kunder registrert";
    }
}

/**
 *Denne Funksjonen oppretter lager en ny kundepeker i liste
 *
 *@param Kunde::Kunde(..)
 **/
void Kunder::nyKunde() {
    if(kundeListe.size() < MAX_PERSONER) {
        sisteNr ++; //teller opp sistenr med en
        //Oppretter ny kunde og flytter den bakerst i listen (holder seg da sortert
        // da sistnr oker med og alle nye legges altid bakerst
        kundeListe.push_back(new Kunde(sisteNr));
    }else cout <<"\nIkke mulig a registrere flere brukere i systemet\n";
}

/**
 *Denne funksjonen leser kunder inn fra fil
 *
 * @see Kunde::Kunde(...)
 **/
void Kunder::kunderLesAlleFraFil(){
    int kundeId; //Brukes for a lese inn kundeid temporert
    ifstream innfil("KUNDER.DTA"); //lager et innfil objekt

    //Kontrollerer at  datastrukt er tom for import
    if(sisteNr == 0 && kundeListe.empty()){
        //Sjekker om jeg far apnet filen
        if(innfil){
            innfil >> sisteNr; //oppdaterer sisteNr
            //Leser inn sa lenge det er data
            innfil >> kundeId;
            //Sa lenge det er elementer pa filen
            while(!innfil.eof()){
               //Lager en ny kunde og sender med filobjekt og kundenr
                kundeListe.push_back(new Kunde(innfil,kundeId));
                innfil >>kundeId;
            }

        }else cout <<"\nFinner ikke fil!";


    }else cout <<"\nFilimport skal kun skje ved oppstart og tom datastruktur!!";
    innfil.close();
}

/**
 *Denne funksjonen finner og skriver ut data for alle kunder
 *
 *@see Kunde::skrivData(..)
 **/
void Kunder::kundeSAlleSkrivData(){
    int teller = 0; //hjelpeint for a stoppe pr 10 utskrift av kunde
    //Sjekker at det er kunder registrert
    if(!kundeListe.empty()){
        //Skriver ut alle kunder ifra listen
        for(const auto & liste :kundeListe) {
            //Pauser for hvert 10 kunde
            if(teller % 10 == 0 && teller != 0){
                cout << '\n';
                system("pause"); //Far bruker a taste enter
            }
            teller++;

            liste -> skrivData(); //Kaller pa kunde lesdata
            cout <<"\n";
        }
    } else cout <<"\nIngen kunder er registrert! ";
}
/**
 *Denne klassefunkjsonen skriver alle kunder til fil
 *
 *@see kunde::skrivTilFil()
 **/
void Kunder::kunderSkrivAlleTilFil(){
    ofstream utfil("KUNDER.DTA");
    //Sa lenge det finnes registrerte kunder:
    if(!kundeListe.empty()){
        utfil << sisteNr <<"\n"; //Legger kunder sistenr pa fil
        //Skriver en og en kunde pa fil
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
    //Sjekker at det finnes kunder registert og i sa fall fortetter
    if(!kundeListe.empty()){
        //nr = lesInt("\nKundenr: ",1,sisteNr); //hvilken kunde ?
        nr = lesIntX(1, sisteNr);
        if (nr != 0)
        {
            //Leter etter kunden
            auto it = find_if(kundeListe.begin(), kundeListe.end(),
                [nr](auto val) {return(val->kundeIdRetur() == nr); });

            //Sa lenge treff pa kunden sa skriver jeg ut data
            if (it != kundeListe.end()) {
                (*it)->skrivData(); //Skriver ut kundens data
            }
            else cout << '\n' << ("Finner ikke kunde med id") << nr;
        }
    }else cout <<"\nIngen kunder er registrert i systemet!";
}

/**
 *Funksjon for ? finne kunde basert p? kundenummer parameter
 *
 * @param int knrParam - variabel for ? holde <knr> fra kommando K O <knr>
 **/
vector <int>  Kunder::finnKundeSone(int knrParam) {
    vector <int> interesseSone;                 //lager vector for ? holde interesse soner til kunden
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
    return kundeListe.empty();
}

/**Denne klassefunksjonen finner og sletter en spesifikk kunde
 *
 *@see Kunde::kundeIdReturn()
 **/
void Kunder::slettKunde() {
     int nr; //Brukes til innlesning
     char konfirmasjon;

    if(!kundeListe.empty()){
    //cout <<"\nHvilken kunde vil du slette? ";
    nr = lesIntX(1, sisteNr);
        if (nr != 0)
        {
            //leter etter kunden
            auto it = find_if(kundeListe.begin(), kundeListe.end(),
                [nr](auto val) {return(val->kundeIdRetur() == nr); });

            //Sa lenge den finnes
            if (it != kundeListe.end()) {
                konfirmasjon = lesChar("\nNB! Hvis du sletter en Kunde er den borte for alltid. Slett? [j/n]");
                if (konfirmasjon == 'J')
                {
                    delete (*it); //Sletter brukerobjektet
                    kundeListe.remove((*it)); //Fjerner peker fra listen
                    cout << "\nBruker med id: " << nr << " er slettet";
                }
                else
                {
                    cout << "Kunden ble ikke slettet.\n";
                }
            }
            else cout << "\nFant ikke Kunde " << nr << ".\n";
        }
    }else cout <<"\nIngen kunder registrert i systemet";
}

