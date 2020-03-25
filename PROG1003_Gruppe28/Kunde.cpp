#include "Const.h"
#include "Kunde.h"
#include "Soner.h"
#include "LesData3.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale> //IS blank
using namespace std;

extern Soner gSoner; //Legger til Gsonr for å kunne utføre sjekk og mappinger
/**
 * Dette er parameterfylt konstruktor, far medsendt id og ber bruker lese inn
 *
 * @param   nr  -   unik id
 * */

Kunde::Kunde(int nr) {
    ID = nr; //Setter medsent nr til ID
    char kommando;
    int soneInnlest; //Bruker for a lese inn en sone.
    //Leser inn data fra bruker

    cout <<"\nNavn: ";
    getline(cin,navn);
    cout <<"\nGate: ";
    getline(cin,gateAddresse);
    cout <<"\nPoststed og nr: ";
    getline(cin,postAdresse);
    cout <<"\nE-post: ";
    getline(cin,mail);
    //Sikrer innlesning av tlfnr
    telefon = lesInt("\nTelefonnummer:",0,99999999);
    //IMPLEMENTERES ENUM OG VECTORINNLESNING
    //Registrerer soner
    cout <<"\nRegistrer sone J trykk Q for avslutt";
    kommando = lesChar("");
    while(kommando !='Q') {
       soneInnlest = lesInt("\nSonenr:",1,MAX_SONER);
       //Sa lenge sonen finnes registrer den
       if(gSoner.finnesSone(soneInnlest)){
        //Sjekker om sonen allerede er registrert (om bruker gjentar seg
        //og for a unga duplikat)
        auto it = find(kundeSoner.begin(),kundeSoner.end(),soneInnlest);
        //Hvis ikke allerede registrert pa kunde, gor dette
        if(it ==kundeSoner.end()){
            kundeSoner.push_back(soneInnlest);
            cout <<"\nSonen: " <<soneInnlest <<"er registrert";
        }
        else cout <<"\nSonenr: " <<soneInnlest <<" allerede registrert";
       }
       else cout <<"\nFinner ikke sonenr: " <<soneInnlest;
      kommando = lesChar("\nRegistrer sone J trykk Q for avslutt");

    }

    //Sorterer intreserte soner i stigende rekkefolge
    sort(kundeSoner.begin(),kundeSoner.end());

}
/**
*Denne funksjonen endrer pa en kundes onsket sone data
*
*@see Kunde::kundeSkrivData(..)
**/
void Kunde::endreData(){
    char kommando;
        //Skriver ut melding til bruker
        cout <<"\nTast L for a legge til soner"
             <<"\nTast F for a fjerne soner"
             <<"\nTast Q for a avbryte";
    //IMPLEMENTER

}

/**
*Denne funksjonen returnerer den unike ID til en kunde
*
*@return ID -   returnerer ID til en person
**/
int Kunde::kundeIdRetur(){
    return ID;
}

/**
 * Denne klassefunksjonen skriver ut den medlemmer pa skjerm
 * */
void Kunde::skrivData() {
    cout <<"\nNavn: " <<navn
              <<"\nAddresse: " <<gateAddresse
              <<"\nPoststed og nr: " <<postAdresse
              <<"\nMailaddresse: " <<mail
              <<"\nTelefon: " <<telefon;
    //IMPLEMENTER ENUM OG VECTORLESNING
   cout <<"\nInteressesoner: ";
    //Sjekker at det er soner registrert og skriver de isafall ut
    if(!kundeSoner.empty()){
        for(auto const & val:kundeSoner){
            cout <<val<<", ";
        }
    }
    //Hvis ingen sone gir tilbakemelding
    else cout <<"\nIngen soner er registrert!";
}

/**
*Denne funksjonen returnerer sonene med boliger kunden er interessert i.
*
*@return kundeSoner -   returnerer kundeSoner vector til en person/kunde
**/
void Kunde::kundeSonerRetur() {
   // return kundeSoner;
}

/**
*Test destructor
**/
Kunde::~Kunde() {
cout <<"\nKunde med navn: "<<navn <<" og id "<<ID <<"Slettes";
}
