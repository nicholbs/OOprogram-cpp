#include "Kunde.h"
#include "LesData3.h"
#include <iostream>
#include <string>
using namespace std;

/**
 * Dette er parameterfylt konstruktor, far medsendt id og ber bruker lese inn
 *
 * @param   nr  -   unik id
 * */

Kunde::Kunde(int nr) {
    ID = nr; //Setter medsent nr til ID
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
