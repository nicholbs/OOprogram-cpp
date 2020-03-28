#include "boligtype.h"
#include "Const.h"
#include "Kunde.h"
#include "Soner.h"
#include "Funksjoner.h"
#include "LesData3.h"
#include <iostream>
#include <string>
#include <vector> //Brukes blant annet til int vektoren sone
#include <algorithm> //Brukes til remove og find algoritmer
#include <iomanip>      //nicholas include pga setw i kunde::kundeSonerRetur()
#include <locale> //IS blank
#include <fstream> //Brukes til filhandtering
using namespace std;

extern Soner gSoner; //Legger til Gsonr for å kunne utføre sjekk og mappinger
/**
 * Dette er parameterfylt konstruktor, far medsendt id og ber bruker lese inn
 *
 * @param   nr  -   unik id
 *@see Kunde::registrerSoner()
 * */

Kunde::Kunde(int nr) {
    ID = nr; //Setter medsent nr til ID
    char kommando;
    int soneInnlest; //Bruker for a lese inn en sone.
    //Leser inn data fra bruker

    cin.ignore();
    skrivNavn(navn); //Registrerer navn
    lesGateAdr(gateAddresse); //Registrerer gateaddresse
    //lesPostAdr(postAdresse);//nye postaddresse fungerer fint men er litt streng, leser inn pa gammel mate
    cout <<"\nPoststed og nr: ";
    getline(cin,postAdresse);
    lesEpostAdr(mail); //Leser mail fra bruker
    //Sikrer innlesning av tlfnr
    telefon = lesInt("\nTelefonnummer:",11111111,99999999);
    //Registrerer interresenn for leilighet eller bolig

    kommando = lesChar("Leilighet/enebolig[L/N]");
    while(kommando !='L' && kommando !='N'){
        if(kommando =='L'){
            boligtype::Enebolig;
        }
        else if (kommando =='N'){
           boligtype::Leilighet;
        }
        else cout <<"\nFATAL feil";
    }

    Kunde::registrerSoner(); //Registrerer soner til kunde.

}
/**
*Denne funksjonen endrer pa en kundes onsket sone data
*
*@see Kunde::kundeSkrivData(..)
**/
void Kunde::endreData(){
    char kommando; //Menyvalg
    int soneInnlest; //Sone valgt

    this->skrivData(); //Skriver ut kundens data

    //Skriver ut melding til bruker
    cout <<"\nTast L for a legge til soner"
         <<"\nTast F for a fjerne soner"
         <<"\nTast Q for a avbryte";

       // this ->registrerSoner(); //Registrerer soner
    kommando=lesChar("\nMenyvalg: "); //Leser inn fra bruker

    while (kommando !='Q') {
        switch(kommando){
            case 'L':
                this ->registrerSoner(); //Registrerer soner
                break;
            case 'F':
                if(!kundeSoner.empty()){
                soneInnlest = lesInt("\nSonenr:",1,MAX_SONER);
                //Sjekker om innlest sone finnes registrert hos bruker
                auto it = find(kundeSoner.begin(),kundeSoner.end(),soneInnlest);
                //Hvis den finnes sa sletter jeg den og sorterer vectoren
                if(it !=kundeSoner.end()){
                    remove(kundeSoner.begin(),kundeSoner.end(),soneInnlest);
                    sort(kundeSoner.begin(),kundeSoner.end());
                    cout <<"\nSonenr: " <<soneInnlest <<" slettet fra bruker";
                }
                else cout <<"\nFinner ikke Sone hos bruker " <<soneInnlest;
             }
             else cout <<"\nIngen soner er registrert pa bruker ";
            default:
                cout <<"\nTast L for a legge til soner"
                <<"\nTast F for a fjerne soner"
                <<"\nTast Q for a avbryte";
                break;
        }
    kommando=lesChar("\nMenyvalg");
    }
}

void Kunde::registrerSoner(){
    int soneInnlest; //Bruker for a lese inn en sone.
    char kommando;
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
void Kunde::skrivTilFil(ofstream & ut) {
    int antIntSoner; //Antall interessesoner for en kunde.
    ut <<ID <<" " <<navn <<"\n";
    ut << telefon <<" " <<mail <<"\n";
    ut << gateAddresse <<"\n";
    ut << postAdresse <<"\n";
    //Her ma det komme en boligtyp
    //Skriver forst antall interessesoner
    antIntSoner = kundeSoner.size();
    ut <<antIntSoner <<" ";
    //Skriver sa ut alle sonenr til fil
    for(const auto & kundesone : kundeSoner) {
        ut <<kundesone <<" ";
    }
    ut <<"\n"; //Legger en enter til neste kunde

}

/**
* Funksjonen returnerer sonene med boliger kunden er interessert i.
*
* @return kundeSoner -   returnerer kunde objektet sin vector av typen int med navn kundeSoner
**/
vector <int> Kunde::kundeSonerRetur() {

    return kundeSoner;
}

/**
*Test destructor
**/
Kunde::~Kunde() {
cout <<"\nKunde med navn: "<<navn <<" og id "<<ID <<"Slettes";
}

