#include "Const.h"
#include "Kunde.h"
#include "Soner.h"
#include "LesData3.h"
#include <iostream>
#include <string>
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
        kundeSoner.push_back(soneInnlest);
       }
       else cout <<"\nFinner ikke sonenr: " <<soneInnlest;

        kommando = lesChar("\nRegistrer sone J trykk Q for avslutt");

    }


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
}
