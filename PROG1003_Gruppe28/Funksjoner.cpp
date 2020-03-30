#include "Funksjoner.h"
#include <iostream>
#include <string>
//#include <locale> //sialpha, is nuermic osv

using namespace std;

/**
*Denne funksjonen validerer og registrerer en e-postaddr
*
*@param -   epost   medsent variabel som skal fa data oppdatert
**/
void lesEpostAdr(std::string & epost){
    int i;
    bool valider;


    do{
        valider =true;
        cout <<"\nE-post addresse: ";
        cin >>epost;
        cin.ignore();

        //Sjekker om epostaddessen inneholder @
        if (epost.find("@") !=string::npos){
            valider = true;
        }else valider = false;
        //Sjekker at epost addresse inneholder minst et punktum
         if (epost.find(".") !=string::npos){
            valider = true;
        } else valider = false;
        //Sjekker teksten og sa lenge den kun inneholder bokstaver, tall - @ .
        for(i= 0; i<epost.size(); i++){
            if(valider == true && (isalpha(epost[i]) ||isdigit(epost[i]) || epost[i] =='-' || epost[i]=='@' || epost[i]=='.')) {
                valider = true;
            }
            else {
                    valider = false;
            }
        }
        if(!valider){
            cout <<"\nIkke gyldig e-post addresse, Ma inneholde @ samt . og kan kun inneholde: "
                 <<"Bokstaver, tall, @ - . ";
        }
    }while(valider == false);
}

/**
*Denne funksjonen validerer og registrerer et gateaddresse
*
* @param    gta -   Medsendt gateaddressevariabel
**/
//Gateaddresse inneholder forst en bokstav derretter ' ' ; - og tall
void lesGateAdr(std::string & gta){
   int i; //Lokketeller
    bool valider =true; //Brukes til a sjekke innlest navn

    do{
        valider = true; //settes til true for a kontrollere lokken
        cout <<"\nGateaddresse: ";
        getline(cin,gta);
            //Sjekker at forste tegn inneholder en bokstav
            if (isalpha(gta[0])){
                for (i = 1; i < gta.size();i++){
                    //Sa lenge string inneholder bokstaver, mellomrom, tall og -
                    if(valider == true && (isalpha(gta[i]) || gta[i]==' ' || isdigit(gta[i])||gta[i]=='-')){
                        valider =true;
                    }
                    else {
                        valider = false;
                    }
                }
            } else valider=false;
    }while(valider ==false);
}

/**
*Denne funksjonen validerer og registrerer en post addresse
*
*@param pad -  medsendt variabel for oppdatering av postaddresse
**/
//forutsettning 3 eller 4 første er tall, etterfulgt med et mellomrom og deretter tekst med . ' ' - eller bokstaver
void lesPostAdr(std::string & pad){
    int i; //Lokketeller
    bool valider = true; //Brukes til sjekk av tekst

    do{
        valider = true;
        cout <<"\nSkriv inn postnr poststed: ";
        getline(cin,pad);
        //Kontrolerer at de 3 forste er tall
        for (i=0;i<=2;i++){
            if(isdigit(pad[i])){
                valider = true;
            } else valider=false;
        }
        //Sjekker deretter at 4 tegn er tall eller mellomrom
        if(valider == true && (isdigit(pad[3]) || pad[3]==' ')){
            valider = true;
        } else valider = false;

        //Hvis det ikke er et mellomrom fra 4 tall og tekst sa skal det forkastes
        if(valider == true && (isdigit(pad[3]) && pad[4] !=' ')) {
            valider = false;
        }
        //Sjekker resten av tekstem kan inneholde bokstaver mellomrom - .
        for(i=5; i <pad.size(); i++) {
            if(valider == true && (isalpha(pad[i])|| pad[i]==' ' || pad[i]== '.' || pad[i]=='-')) {
                valider = true;
            } else valider = false;
        }
        if(!valider){
            cout <<"\nUgyldig sammensettning av postnr og poststed"
                 <<", Kan kun inneholde bokstaver, tall, mellomrom, punktum, bindestrek"
                 <<" og Ma skrives pa format:\n"
                 <<"tre tall mellomrom etterfulgt av bokstaver, punktum og bindestrek eller:\n"
                 <<"fire tall mellomrom etterfulgt av bokstaver, punktum og bindestrek";
        }
    }while(valider == false);

}
/**
*Denne funksjonen validerer og registrerer et navn
*
*param  @nvn    -   navn
**/
//Tilater mellomrom og alfa.
void skrivNavn(string & nvn){
    int i; //Lokketeller
    bool valider =true; //Brukes til a sjekke innlest navn

    do{
        valider = true; //settes til true for a kontrollere lokken
        cout <<"\nNavn: ";
        getline(cin,nvn);
            for (i = 0; i < nvn.size();i++){
                //Sa lenge string inneholder bokstaver eller mellomrom
                if(valider == true && (isalpha(nvn[i]) || nvn[i]==' ')){
                    valider =true;
                }
            else {
                valider = false;
            }
        }
        if(!valider){
            cout <<"\nUgyldig navnformat, Kan kun besta av bokstaver og mellomrom!";
        }

    }while(valider ==false);
}
