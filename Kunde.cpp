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
 * Dette er parameterfylt konstruktor, far medsendt id og ber bruker lese inn data
 *
 * @param   nr  -   unik id
 * @see Kunde::registrerSoner()
 * @see lesEpostAdr()
 * @see lesGateAdr()
 * @see lesPostAdr()
 * @see skrivNavn()
 * */
Kunde::Kunde(int nr) {
    ID = nr; //Setter medsent nr til ID
    char kommando = ' ';
     cout <<"\nKundeid: " <<nr;
    //Leser inn data fra bruker
    cin.ignore();
    skrivNavn(navn); //Registrerer navn
    lesGateAdr(gateAddresse); //Registrerer gateaddresse
    lesPostAdr(postAdresse);//Leser postaddresse
    lesEpostAdr(mail); //Leser mail fra bruker
    cin.ignore();
    telefon = lesInt("\nTelefonnummer:",11111111,99999999); //Sikrer innlesning av tlfnr
    kommando = lesChar("Leilighet/Enebolig [L/E]");         //Registrerer interresenn for leilighet eller bolig
    do
    {    
        if(kommando == 'L')
            boligType = boligtype::Leilighet;
        else if (kommando =='E')
            boligType=boligtype::Enebolig;
        else 
            cout <<"\nVennligst velg enten [L]eilighet eller [E]nebolig.\n";
    } while (kommando != 'L' && kommando != 'E');

    Kunde::registrerSoner(); //Registrerer soner til kunde.

}
/**
 *Denne konstructoren registrerer ny kunde fra fil
 *
 *@param ifstream    -   filobjekt
 *@param kId         -   medsendt kundeid
 **/
Kunde::Kunde(ifstream & inn, int kId) {
    int tempSoneInnlest; //brukes for a lese inn sone etter sone
    int tempBoligType; //Brukes til innlesning og omcasting boligtype
    int antSoner; //Brukes til loop for soneinnlesning
    int i; //Lokketeller
    ID = kId;
    inn.ignore();
    getline(inn,navn);
    inn >> telefon;
    inn.ignore();
    getline(inn,mail);
    getline(inn,gateAddresse);
    getline(inn,postAdresse);
    //Leser inn og registrerr int boligtype
    inn >> tempBoligType;
    //Caster om og registrer boligtypen basert pa innlest ing
    boligType = static_cast<boligtype>(tempBoligType);
    //Leser inn interessesoner
    inn >> antSoner;

    //Looper igjennom og registrerer i vectoren, tall skal allerede vare sortert
    for(i = 0; i<antSoner; i++) {
        inn >> tempSoneInnlest; //leser inn en sone
        kundeSoner.push_back(tempSoneInnlest); //Putter sonen bakerst i vector
    }

    //Egentlig skal ALT allerede vare sortert, men tar dette for sikkerhetskyld
    sort(kundeSoner.begin(),kundeSoner.end());
}
/**
 *Denne funksjonen endrer pa en kundes onsket sone data
 *
 * @see Kunde::kundeSkrivData(..)
 * @see Kunde::registrerSoner()
 **/
void Kunde::endreData(){
    char kommando; //Menyvalg
    int soneInnlest; //Sone valgt

    this->skrivData(); //Skriver ut kundens data

    cout << "\n\n[L] - Legg til soner"
         << "\n[F] - Fjern sone"
         << "\n[Q] - Avbryt\n";

    kommando = lesChar("~Menyvalg"); //Leser inn fra bruker

    while (kommando !='Q') {
        switch(kommando){
        case 'L':
            registrerSoner(); //Registrerer soner
            break;
        case 'F':
            //sa lenge det finnes registrerte soner kan man fjerne en sone
            if(!kundeSoner.empty())
            {
                soneInnlest = lesInt("Sonenr:",1,MAX_SONER);

                //Sjekker om innlest sone finnes registrert hos bruker
                auto it = find(kundeSoner.begin(),kundeSoner.end(),soneInnlest);
                if(it !=kundeSoner.end())
                {
                    kundeSoner.erase(it);
                    sort(kundeSoner.begin(),kundeSoner.end());
                    cout <<"Sonenr: " <<soneInnlest <<" slettet fra bruker";
                }
                else 
                    cout <<"\nFinner ikke Soner:" <<soneInnlest<<" hos bruker\n";
            }
            else 
                cout <<"\nIngen soner er registrert pa bruker\n";
            break;
        default:
            cout << "\n\n[L] - Legg til soner"
                << "\n[F] - Fjern sone"
                << "\n[Q] - Avbryt\n";
        }
    kommando = lesChar("\n~Menyvalg");
    }
}
/**
 * Denne klassefuksjonen registrerer soner hos en kunde
 *
 *@see Soner::finnesSone()
 *@see Soner::isEmpty()
 **/
void Kunde::registrerSoner(){
    int soneInnlest; //Bruker for a lese inn en sone.
    char kommando; //Registrerr brukerens menyvalg

    //Sjekker at det er soner og fortsetter hvis det er
    if(!gSoner.isEmpty()){
        cout << "\n[R] - Registrer sone"
             << "\n[Q] - Avbryt\n";
        kommando = lesChar("~Menyvalg");

        while(kommando !='Q') 
        {
            soneInnlest = lesInt("\nSonenr:",1,MAX_SONER);
            //Sa lenge sonen finnes registrer den
            if(gSoner.finnesSone(soneInnlest))
            {
                //Sjekker om sonen allerede er registrert (om bruker gjentar seg
                //og for a unga duplikat)
                auto it = find(kundeSoner.begin(),kundeSoner.end(),soneInnlest);

                //Hvis ikke allerede registrert pa kunde, gor dette
                if(it ==kundeSoner.end())
                {
                    kundeSoner.push_back(soneInnlest);
                    cout <<"\nSone " <<soneInnlest <<" er registrert\n";
                }
                else cout <<"\nSone " <<soneInnlest <<" er allerede registrert\n";
            }
            else cout <<"\nFant ikke sone " << soneInnlest << ".\n";

            cout << "\n[R] - Registrer sone"
                 << "\n[Q] - Avbryt\n";
            kommando = lesChar("~Menyvalg");
        }

    //Sorterer intreserte soner i stigende rekkefolge
    sort(kundeSoner.begin(),kundeSoner.end());
    }else cout <<"\nFinnes ingen soner i systemet.\n";

}


/**
 *Denne klassefunksjonen returnerer den unike ID til en kunde
 *
 *@return ID -   returnerer ID til en person
 **/
int Kunde::kundeIdRetur(){
    return ID;
}

string Kunde::getNavn()
{
	return navn;
}

/**
 * Denne klassefunksjonen skriver kundens data pa skjerm
 * */
void Kunde::skrivData() {
    cout <<"\nKundeid: " <<ID;
    cout <<"\nNavn: " <<navn
              <<"\nAddresse: " <<gateAddresse
              <<"\nPoststed og nr: " <<postAdresse
              <<"\nMailaddresse: " <<mail
              <<"\nTelefon: " <<telefon;
    //Skriver ut basert pa enum om det er Enebolig eller Leilighet
    cout <<"\nType: ";
    if(boligType == boligtype::Enebolig) {
        cout <<"Enebolig";
    }
    else if(boligType ==boligtype::Leilighet){
        cout <<"Leilighet";
    }
    cout <<"\nAntall interessesoner: " << kundeSoner.size();
    //Skriver ut hele vectoren med interessesoner
    cout <<"\nInteressesoner: ";
    //Sjekker at det er soner registrert og skriver de isafall ut
    if(!kundeSoner.empty()){
        for(const auto & val:kundeSoner){
            cout <<val<<", ";
        }
    }
    //Hvis ingen sone gir tilbakemelding
    else cout <<"\nIngen soner er registrert pa bruker!";
}

/**
 *Denne funksjonen skriver en kunde til fil
 *
 *@param ut  -   et ofstrem objekt
 **/
void Kunde::skrivTilFil(ofstream & ut) {
    int antIntSoner; //Antall interessesoner for en kunde.
    int enumKonertering; //Brukes til a konvertere fra enum til int
    //Konverterr enum til int
    enumKonertering = static_cast<int>(boligType);
    //Skriver dataelementer til fil
    ut <<ID <<" " <<navn <<"\n";
    ut << telefon <<" " <<mail <<"\n";
    ut << gateAddresse <<"\n";
    ut << postAdresse <<"\n";
    ut <<enumKonertering <<"\n";
    //Skriver forst antall interessesoner il fil
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
//cout <<"\nKunde med navn: "<<navn <<" og id "<<ID <<"Slettes";
}

