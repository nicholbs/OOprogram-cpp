#include "Funksjoner.h"
#include <iostream>
#include <string>
//#include <locale> //sialpha, is nuermic osv

using namespace std;


/**
*Denne funksjonen validerer og registrerer et gateaddresse
*
**/
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
                    if(valider == true && (isalpha(gta[i]) || gta[i]==' ' || isdigit(gta[i]))||gta[i]=='-'){
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

    }while(valider ==false);
}
